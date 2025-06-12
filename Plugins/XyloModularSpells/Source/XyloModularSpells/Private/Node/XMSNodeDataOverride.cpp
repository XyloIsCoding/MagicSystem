// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/XMSNodeDataOverride.h"

#include "Node/XMSNodeRegistry.h"
#include "Node/XMSNodeTypes.h"


UXMSNodeDataOverride::UXMSNodeDataOverride(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Display, TEXT("Building Data Override Array"))

	// TODO: instead of resetting delete elements not contained in FXMSNodeRegistry::Registry and add missing ones
	Registry.Reset();
	TArray<FGameplayTag> NodeIds;
	FXMSNodeRegistry::Registry.GetKeys(NodeIds);
	for (FGameplayTag NodeId : NodeIds)
	{
		Registry.Add(FXMSNodeData(NodeId));
	}
}

void UXMSNodeDataOverride::TestFunction()
{
	
}
