// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Base/XMSNodeWithMap.h"

#include "XMSModularSpellsSubsystem.h"
#include "XMSNodeStaticLibrary.h"
#include "XMSTypes.h"
#include "XyloModularSpells.h"
#include "Node/XMSNodeContainer.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// Serialization

TSharedPtr<FJsonObject> UXMSNodeWithMap::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);

	// Serialize sub-nodes recursively
	for (TPair<FName, FXMSNodeContainer*>& SubNode : SubNodes)
	{
		if (!SubNode.Value)
		{
			UE_LOG(LogXyloModularSpells, Error, TEXT("UXMSNodeWithMap::SerializeToJson >> Sub-node container ptr not found for [%s]"), *SubNode.Key.ToString())
			continue;
		}

		if (UXMSNode* Node = SubNode.Value->GetGeneric())
		{
			bool bSerializedSubNode;
			TSharedPtr<FJsonObject> SubNodeJson = Node->SerializeToJson(bSerializedSubNode);

			// Avoid adding the object containing this sub-node if it was not serialized
			if (bSerializedSubNode)
			{
				NodeJson->SetObjectField(SubNode.Key.ToString(), SubNodeJson);
			}
		}
	}
	
	return NodeJson;
}

void UXMSNodeWithMap::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);
	
	// Instantiate sub-nodes of the appropriate class and initialize them recursively
	for (TPair<FName, FXMSNodeContainer*>& SubNode : SubNodes)
	{
		if (!SubNode.Value)
		{
			UE_LOG(LogXyloModularSpells, Error, TEXT("UXMSNodeWithMap::SerializeToJson >> Sub-node container ptr not found for [%s]"), *SubNode.Key.ToString())
			continue;
		}

		// Get data relative to this sub-node
		const TSharedPtr<FJsonObject>* SubNodeJsonObjectPtr;
		if (!JsonObject->TryGetObjectField(SubNode.Key.ToString(), SubNodeJsonObjectPtr))
		{
			// No sub-node data for this sub-node;
			continue;
		}
		TSharedPtr<FJsonObject> SubNodeJsonObject = *SubNodeJsonObjectPtr;

		// Get sub-node Class Name
		FString SubNodeClassName;
		if (!SubNodeJsonObject->TryGetStringField(NodeClassJsonKey, SubNodeClassName))
		{
			// Could not get class for sub-node
			continue;
		}
		// Set sub-node and initialize it
		UClass* SubNodeClass = UXMSNodeStaticLibrary::GetNodeClassByName(SubNodeClassName);
		if (SubNode.Value->IsCompatible(SubNodeClass))
		{
			if (UXMSNode* NewSubNode = NewObject<UXMSNode>(GetOuter(), SubNodeClass))
			{
				SubNode.Value->SetGeneric(NewSubNode);
				NewSubNode->DeserializeFromJson(SubNodeJsonObject);
			}
		}
	}
}

// ~Serialization
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// SubNodes

UXMSNode* UXMSNodeWithMap::GetSubNode(const FXMSNodePathElement& PathElement) const
{
	return GetSubNode(PathElement.Identifier);
}

void UXMSNodeWithMap::GetAllSubNodes(FXMSNodeQueryResult& OutNodes) const
{
	for (const TPair<FName, FXMSNodeContainer*>& SubNode : SubNodes)
	{
		if (!SubNode.Value)
		{
			UE_LOG(LogXyloModularSpells, Error, TEXT("UXMSNodeWithMap::GetAllSubNodes >> Sub-node container ptr not found for [%s]"), *SubNode.Key.ToString())
			continue;
		}
		OutNodes.Nodes.Add(FXMSNodePathElement(SubNode.Key), SubNode.Value->GetGeneric());
	}
}

void UXMSNodeWithMap::GetAllSubNodes(TArray<UXMSNode*>& OutNodes) const
{
	for (const TPair<FName, FXMSNodeContainer*>& SubNode : SubNodes)
	{
		if (!SubNode.Value)
		{
			UE_LOG(LogXyloModularSpells, Error, TEXT("UXMSNodeWithMap::GetAllSubNodes >> Sub-node container ptr not found for [%s]"), *SubNode.Key.ToString())
			continue;
		}
		OutNodes.Add(SubNode.Value->GetGeneric());
	}
}

void UXMSNodeWithMap::SetSubNode(const FXMSNodePathElement& PathElement, UXMSNode* InNode)
{
	SetSubNode(PathElement.Identifier, InNode);
}

void UXMSNodeWithMap::GetSubNodeClassOptions(const FXMSNodePathElement& PathElement, TArray<TSubclassOf<UXMSNode>>& OutClassOptions)
{
	FXMSNodeContainer** NodeContainerFound = SubNodes.Find(PathElement.Identifier);
	if (!NodeContainerFound)
	{
		UE_LOG(LogXyloModularSpells, Error, TEXT("UXMSNodeWithMap::GetAllSubNodes >> Sub-node container ptr not found for [%s]"), *PathElement.Identifier.ToString())
		return;
	}
	
	TArray<TSubclassOf<UXMSNode>> NodeClasses;
	UXMSNodeStaticLibrary::GetAllNodeClasses(NodeClasses);

	FXMSNodeContainer* NodeContainer = *NodeContainerFound;
	OutClassOptions = NodeClasses.FilterByPredicate([NodeContainer](UClass* NodeClass)
	{
		return NodeContainer->IsCompatible(NodeClass);
	});
}

void UXMSNodeWithMap::GetSubNodesIdentifiers(TArray<FName>& OutIdentifiers) const
{
	SubNodes.GetKeys(OutIdentifiers);
}

// ~SubNodes
/*--------------------------------------------------------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWithMap
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// SubNodes

UXMSNode* UXMSNodeWithMap::GetSubNode(FName Identifier) const
{
	FXMSNodeContainer* const* ContainerPtrPtr = SubNodes.Find(Identifier);
	if (!ContainerPtrPtr) return nullptr;

	return (*ContainerPtrPtr)->GetGeneric();
}

void UXMSNodeWithMap::SetSubNode(FName Identifier, UXMSNode* InNode)
{
	FXMSNodeContainer** ContainerPtrPtr = SubNodes.Find(Identifier);
	if (!ContainerPtrPtr) return;

	(*ContainerPtrPtr)->SetGeneric(InNode);
}

void UXMSNodeWithMap::OnSubNodeChanged(FName Identifier)
{
}

// ~SubNodes
/*--------------------------------------------------------------------------------------------------------------------*/

