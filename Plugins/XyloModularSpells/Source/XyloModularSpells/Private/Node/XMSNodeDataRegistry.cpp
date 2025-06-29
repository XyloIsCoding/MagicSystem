// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/XMSNodeDataRegistry.h"

#include "XMSModularSpellsSubsystem.h"
#include "Node/Base/XMSNode.h"


void FXMSNodeData::UpdateSubNodes()
{
	if (NodeClass)
	{
		// Get sub-nodes identifiers
		UXMSNode* DefaultNode = NodeClass->GetDefaultObject<UXMSNode>();
		TArray<FName> SubNodesIdentifiers;
		DefaultNode->GetSubNodesIdentifiers(SubNodesIdentifiers);

		TArray<FXMSSubNodeData> TempArray;
		for (FName Identifier : SubNodesIdentifiers)
		{
			// Add entry or get existing one
			FXMSSubNodeData* OldData = SubNodes.FindByPredicate([Identifier](const FXMSSubNodeData& SubNodeData )
			{
				return Identifier.IsEqual(SubNodeData.Identifier);
			});
			if (OldData)
			{
				//UE_LOG(LogTemp, Warning, TEXT("FXMSNodeData::UpdateSubNodes >> Retriving %s"), *Identifier.ToString())
				TempArray.Add(*OldData);
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("FXMSNodeData::UpdateSubNodes >> Adding %s"), *Identifier.ToString())
				TempArray.Add(FXMSSubNodeData(Identifier));
			}
		}

		SubNodes.Empty(TempArray.Num());
		SubNodes.Append(TempArray);
	}
}

FXMSSubNodeData* FXMSNodeData::GetSubNodeData(FName SubNodeIdentifier)
{
	return SubNodes.FindByPredicate([SubNodeIdentifier](const FXMSSubNodeData& SubNodeData)
	{
		return SubNodeData.Identifier.IsEqual(SubNodeIdentifier);
	});
}

UXMSNodeDataRegistry::UXMSNodeDataRegistry(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UpdateNodeDataArray();

	if (UXMSModularSpellsSubsystem* MSS = UXMSModularSpellsSubsystem::Get())
	{
		MSS->RegisterNodeDataRegistry(this);
	}
}



#if WITH_EDITOR

void UXMSNodeDataRegistry::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UpdateNodeDataArray();
}

#endif

bool UXMSNodeDataRegistry::GetNodeData(UClass* NodeClass, FXMSNodeData& OutNodeData)
{
	FXMSNodeData* FoundData = NodesData.FindByPredicate([NodeClass](const FXMSNodeData& NodeData){ return NodeData.NodeClass == NodeClass; });
	if (!FoundData) return false;

	OutNodeData = *FoundData;
	return true;
}

FXMSNodeData* UXMSNodeDataRegistry::GetNodeData(UClass* NodeClass)
{
	return NodesData.FindByPredicate([NodeClass](const FXMSNodeData& NodeData){ return NodeData.NodeClass == NodeClass; });
}

void UXMSNodeDataRegistry::UpdateNodeDataArray()
{
	UXMSModularSpellsSubsystem* NodesSubsystem = UXMSModularSpellsSubsystem::Get();
	if (!NodesSubsystem)
	{
		//UE_LOG(LogTemp, Warning, TEXT("UXMSNodeDataRegistry::UpdateNodeDataArray >> UXMSModularSpellsSubsystem not found"))
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("UXMSNodeDataRegistry::UpdateNodeDataArray >> Updating NodesData"))
	
	TArray<FXMSNodeData> TempArray;
	for (UClass* NodeClass : NodesSubsystem->GetNodeClasses())
	{
		// Add entry or get existing one
		FXMSNodeData* OldData = NodesData.FindByPredicate([NodeClass](const FXMSNodeData& NodeData ){ return NodeClass == NodeData.NodeClass; });
		if (OldData)
		{
			//UE_LOG(LogTemp, Warning, TEXT("UXMSNodeDataRegistry::UpdateNodeDataArray >> Retriving %s"), *NodeClass->GetName())
			TempArray.Add(*OldData);
			OldData->UpdateSubNodes();
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("UXMSNodeDataRegistry::UpdateNodeDataArray >> Adding %s"), *NodeClass->GetName())
			TempArray.Add(FXMSNodeData(NodeClass));
		}
	}
	
	NodesData.Empty(TempArray.Num());
	NodesData.Append(TempArray);
}
