// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/XMSNodeDataOverride.h"

#include "XMSModularSpellsSubsystem.h"


UXMSNodeDataOverride::UXMSNodeDataOverride(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UpdateNodeDataArray();
}

bool UXMSNodeDataOverride::GetNodeData(UClass* NodeClass, FXMSNodeData& OutNodeData)
{
	FXMSNodeData* FoundData = NodesData.FindByPredicate([NodeClass](const FXMSNodeData& NodeData){ return NodeData.NodeClass == NodeClass; });
	if (!FoundData) return false;

	OutNodeData = *FoundData;
	return true;
}

void UXMSNodeDataOverride::UpdateNodeDataArray()
{
	UXMSModularSpellsSubsystem* NodesSubsystem = UXMSModularSpellsSubsystem::Get();
	if (!NodesSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("UXMSNodeDataOverride::UpdateNodeDataArray >> UXMSModularSpellsSubsystem not found"))
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("UXMSNodeDataOverride::UpdateNodeDataArray >> Updating NodesData"))
	// TODO: instead of resetting delete elements not contained in FXMSNodeRegistry::NodesData and add missing ones
	// TODO: find a way to actually update the array, cause editor fights with c++ changes
	NodesData.Empty();
	for (UClass* NodeClass : NodesSubsystem->GetNodeClasses())
	{
		UE_LOG(LogTemp, Warning, TEXT("UXMSNodeDataOverride::UpdateNodeDataArray >> Adding %s"), *NodeClass->GetName())
		NodesData.Add(FXMSNodeData(NodeClass));
	}
	
}
