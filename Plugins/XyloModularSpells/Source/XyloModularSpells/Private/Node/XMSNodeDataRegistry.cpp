// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/XMSNodeDataRegistry.h"

#include "XMSModularSpellsSubsystem.h"
#include "Node/XMSNodeData.h"
#include "Node/Base/XMSNode.h"



UXMSNodeDataRegistry::UXMSNodeDataRegistry(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UpdateNodeDataMap();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UObject Interface
 */

#if WITH_EDITOR

void UXMSNodeDataRegistry::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName().IsEqual(GET_MEMBER_NAME_CHECKED(ThisClass, NodesData)))
	{
		UpdateNodeDataMap();
	}
}

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeDataRegistry
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// NodesData

UXMSNodeData* UXMSNodeDataRegistry::GetNodeData(UClass* NodeClass)
{
	if (UXMSNodeData** NodeDataPtr = NodesData.Find(NodeClass))
	{
		return *NodeDataPtr;
	}
	return nullptr;
}

void UXMSNodeDataRegistry::UpdateNodeDataMap()
{
	UXMSModularSpellsSubsystem* NodesSubsystem = UXMSModularSpellsSubsystem::Get();
	if (!NodesSubsystem) return;
	
	for (UClass* NodeClass : NodesSubsystem->GetNodeClasses())
	{
		UXMSNodeData*& NodeDataPtrRef = NodesData.FindOrAdd(NodeClass);
		if (NodeDataPtrRef && NodeDataPtrRef->GetNodeClass() != NodeClass)
		{
			// Resetting ptr if asset defines a wrong class
			NodeDataPtrRef = nullptr;
		}
	}
}

// ~NodesData
/*--------------------------------------------------------------------------------------------------------------------*/

