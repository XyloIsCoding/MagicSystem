// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/XMSNodeDataRegistry.h"

#include "XMSModularSpellsSubsystem.h"
#include "Node/XMSNodeData.h"
#include "Node/Base/XMSNode.h"



UXMSNodeDataRegistry::UXMSNodeDataRegistry(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UpdateNodeDataMap();
	UpdateTypesMap();
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
	else if (PropertyChangedEvent.GetPropertyName().IsEqual(GET_MEMBER_NAME_CHECKED(ThisClass, ValueTypesData)))
	{
		UpdateTypesMap();
	}
}

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeDataRegistry
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// ValueTypes

const TMap<FGameplayTag, FXMSValueTypeData>& UXMSNodeDataRegistry::GetTypesData()
{
	return ValueTypesData;
}

bool UXMSNodeDataRegistry::GetTypeData(const FGameplayTag& InType, FXMSValueTypeData& OutTypeData)
{
	if (FXMSValueTypeData* FoundData = ValueTypesData.Find(InType))
	{
		OutTypeData = *FoundData;
		return true;
	}
	return false;
}

FXMSValueTypeData* UXMSNodeDataRegistry::GetTypeData(const FGameplayTag& InType)
{
	return ValueTypesData.Find(InType);
}

void UXMSNodeDataRegistry::UpdateTypesMap()
{
	ValueTypesData.FindOrAdd(XMSValueType::None);
	ValueTypesData.FindOrAdd(XMSValueType::Bool);
	ValueTypesData.FindOrAdd(XMSValueType::Integer);
	ValueTypesData.FindOrAdd(XMSValueType::Float);
	ValueTypesData.FindOrAdd(XMSValueType::Vector);
	ValueTypesData.FindOrAdd(XMSValueType::Rotator);
	ValueTypesData.FindOrAdd(XMSValueType::String);
	ValueTypesData.FindOrAdd(XMSValueType::Object);
}

// ~ValueTypes
/*--------------------------------------------------------------------------------------------------------------------*/

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
	
	for (UClass* NodeClass : NodesSubsystem->GetNativeNodeClasses())
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

