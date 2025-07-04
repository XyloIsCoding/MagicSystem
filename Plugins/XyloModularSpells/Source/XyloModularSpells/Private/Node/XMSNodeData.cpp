// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/XMSNodeData.h"

#include "Node/Base/XMSNodeWithValue.h"


UXMSNodeData::UXMSNodeData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OnNodeClassChanged();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UObject Interface
 */

#if WITH_EDITOR

void UXMSNodeData::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName().IsEqual(GET_MEMBER_NAME_CHECKED(ThisClass, NodeClass)))
	{
		OnNodeClassChanged();
	}
}

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeData
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// NodeClass

UClass* UXMSNodeData::GetNodeClass() const
{
	return NodeClass;
}

void UXMSNodeData::OnNodeClassChanged()
{
	bIsNodeWithValue = NodeClass && NodeClass->IsChildOf(UXMSNodeWithValue::StaticClass());
	UpdateSubNodes();
}

// ~NodeClass
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// SubNodes

void UXMSNodeData::UpdateSubNodes()
{
	if (!NodeClass) return;
	
	// Get sub-nodes identifiers
	UXMSNode* DefaultNode = NodeClass->GetDefaultObject<UXMSNode>();
	TArray<FName> SubNodesIdentifiers;
	DefaultNode->GetSubNodesIdentifiers(SubNodesIdentifiers);

	TArray<FXMSSubNodeData> TempArray;
	for (FName Identifier : SubNodesIdentifiers)
	{
		// Add entry or get existing one
		FXMSSubNodeData* OldData = SubNodes.FindByPredicate([Identifier](const FXMSSubNodeData& SubNodeData)
		{
			return Identifier.IsEqual(SubNodeData.Identifier);
		});
		if (OldData)
		{
			//UE_LOG(LogTemp, Warning, TEXT("UXMSNodeData::UpdateSubNodes >> Retriving %s"), *Identifier.ToString())
			TempArray.Add(*OldData);
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("UXMSNodeData::UpdateSubNodes >> Adding %s"), *Identifier.ToString())
			TempArray.Add(FXMSSubNodeData(Identifier));
		}
	}

	SubNodes.Empty(TempArray.Num());
	SubNodes.Append(TempArray);
}

bool UXMSNodeData::GetSubNodeData(FName SubNodeIdentifier, FXMSSubNodeData& OutSubNodeData)
{
	if (FXMSSubNodeData* SubNodeData = GetSubNodeData(SubNodeIdentifier))
	{
		OutSubNodeData = *SubNodeData;
		return true;
	}
	return false;
}

FXMSSubNodeData* UXMSNodeData::GetSubNodeData(FName SubNodeIdentifier)
{
	return SubNodes.FindByPredicate([SubNodeIdentifier](const FXMSSubNodeData& SubNodeData)
	{
		return SubNodeData.Identifier.IsEqual(SubNodeIdentifier);
	});
}

// ~SubNodes
/*--------------------------------------------------------------------------------------------------------------------*/

