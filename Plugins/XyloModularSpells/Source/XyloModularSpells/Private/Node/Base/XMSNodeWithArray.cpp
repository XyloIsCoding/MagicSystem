// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Base/XMSNodeWithArray.h"

#include "XMSNodeStaticLibrary.h"
#include "XMSTypes.h"
#include "Node/XMSNodeContainer.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSNodeWithArray::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);

	if (!SubNodes.Value)
	{
		UE_LOG(LogTemp, Error, TEXT("UXMSNodeWithArray::SerializeToJson >> Sub-node container ptr not found for [%s]"), *SubNodes.Key.ToString())
		return NodeJson;
	}

	// Serialize sub-nodes recursively
	bool bSerializedAny = false;
	TArray<TSharedPtr<FJsonValue>> SubNodesJsonArray;
	for (UXMSNode* SubNode : SubNodes.Value->GetAllGeneric())
	{
		bool bSerializedSubNode = false;
		TSharedPtr<FJsonObject> SubNodeJson = SubNode? SubNode->SerializeToJson(bSerializedSubNode) : MakeShareable<>(new FJsonObject);
		SubNodesJsonArray.Add(MakeShareable(new FJsonValueObject(SubNodeJson)));
		bSerializedAny |= bSerializedSubNode;
	}

	// Avoid adding the array containing all sub-nodes if none of them was serialized
	if (bSerializedAny)
	{
		NodeJson->SetArrayField(SubNodes.Key.ToString(), SubNodesJsonArray);
	}
	
	return NodeJson;
}

void UXMSNodeWithArray::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);

	if (!SubNodes.Value)
	{
		UE_LOG(LogTemp, Error, TEXT("UXMSNodeWithArray::DeserializeFromJson >> Sub-node container ptr not found for [%s]"), *SubNodes.Key.ToString())
		return;
	}
	
	const TArray<TSharedPtr<FJsonValue>>* SubNodesJsonArrayPtr;
	if (!JsonObject->TryGetArrayField(SubNodes.Key.ToString(), SubNodesJsonArrayPtr))
	{
		// No sub-nodes array. We can stop here since there is no data to initialize sub-nodes with
		return;
	}

	// Instantiate sub-nodes of the appropriate class and initialize them recursively
	for (const TSharedPtr<FJsonValue>& SubNodeJson : *SubNodesJsonArrayPtr)
	{
		TSharedPtr<FJsonObject> SubNodeJsonObject = SubNodeJson->AsObject();

		// Get sub-node Class Name
		FString SubNodeClassName;
		if (!SubNodeJsonObject->TryGetStringField(NodeClassJsonKey, SubNodeClassName))
		{
			// Could not get class for sub-node
			continue;
		}
		// Set sub-node and initialize it
		UClass* SubNodeClass = UXMSNodeStaticLibrary::GetNodeClassByName(SubNodeClassName);
		if (SubNodes.Value->IsCompatible(SubNodeClass))
		{
			if (UXMSNode* NewSubNode = NewObject<UXMSNode>(GetOuter(), SubNodeClass))
			{
				SubNodes.Value->AddGeneric(NewSubNode);
				NewSubNode->DeserializeFromJson(SubNodeJsonObject);
			}
		}
	}
}

UXMSNode* UXMSNodeWithArray::GetSubNode(const FXMSNodePathElement& PathElement)
{
	if (PathElement.Identifier != SubNodes.Key) return nullptr;
	return GetSubNode(PathElement.Index);
}

void UXMSNodeWithArray::GetAllSubNodes(FXMSNodeQueryResult& OutNodes)
{
	if (!SubNodes.Value)
	{
		UE_LOG(LogTemp, Error, TEXT("UXMSNodeWithArray::GetAllSubNodes >> Sub-node container ptr not found for [%s]"), *SubNodes.Key.ToString())
		return;
	}
	for (auto It = SubNodes.Value->GetAllGeneric().CreateIterator(); It; ++It)
	{
		OutNodes.Nodes.Emplace(FXMSNodePathElement(SubNodes.Key, It.GetIndex()), *It);
	}
}

void UXMSNodeWithArray::SetSubNode(const FXMSNodePathElement& PathElement, UXMSNode* InNode)
{
	if (PathElement.Identifier != SubNodes.Key) return;
	SetSubNode(PathElement.Index, InNode);
}

void UXMSNodeWithArray::GetSubNodesIdentifiers(TArray<FName>& OutIdentifiers) const
{
	OutIdentifiers.Add(SubNodes.Key);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWithArray
 */

UXMSNode* UXMSNodeWithArray::GetSubNode(int32 Index)
{
	FXMSMultiNodeContainer* ContainerPtr = SubNodes.Value;
	if (!ContainerPtr) return nullptr;

	return ContainerPtr->GetGeneric(Index);
}

void UXMSNodeWithArray::SetSubNode(int32 Index, UXMSNode* InNode)
{
	FXMSMultiNodeContainer* ContainerPtr = SubNodes.Value;
	if (!ContainerPtr) return;

	ContainerPtr->SetGeneric(Index, InNode);
}

void UXMSNodeWithArray::AddSubNode(UXMSNode* InNode)
{
	FXMSMultiNodeContainer* ContainerPtr = SubNodes.Value;
	if (!ContainerPtr) return;

	ContainerPtr->AddGeneric(InNode);
}

void UXMSNodeWithArray::InsertSubNode(int32 Index, UXMSNode* InNode)
{
	FXMSMultiNodeContainer* ContainerPtr = SubNodes.Value;
	if (!ContainerPtr) return;

	ContainerPtr->InsertGeneric(Index, InNode);
}

void UXMSNodeWithArray::RemoveSubNode(int32 Index)
{
	FXMSMultiNodeContainer* ContainerPtr = SubNodes.Value;
	if (!ContainerPtr) return;

	ContainerPtr->Remove(Index);
}

void UXMSNodeWithArray::OnSubNodeChanged(FName Identifier, int32 Index)
{
}
