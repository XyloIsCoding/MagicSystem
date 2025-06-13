// Fill out your copyright notice in the Description page of Project Settings.


#include "XMSModularSpellsSubsystem.h"
#include "Node/Base/XMSNode.h"


void FXMSNodeClassCache::InitForType(UClass* InClass)
{
	Classes.Reset();

	// Find all script structs of this type and add them to the list
	// (not sure of a better way to do this but it should only happen once at startup)
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(InClass) && !It->HasAnyClassFlags(CLASS_Abstract))
		{
			Classes.Add(*It);
		}
	}
	
	Classes.Sort([](const UClass& A, const UClass& B) { return A.GetName().ToLower() > B.GetName().ToLower(); });
}

UXMSModularSpellsSubsystem* UXMSModularSpellsSubsystem::Get()
{
	if (!GEngine) return nullptr;
	return GEngine->GetEngineSubsystem<UXMSModularSpellsSubsystem>();
}

void UXMSModularSpellsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	NodeClassCache.InitForType(UXMSNode::StaticClass());
}

void UXMSModularSpellsSubsystem::RegisterNodeDataOverride(UXMSNodeDataOverride* InNodeDataOverride)
{
	if (!InNodeDataOverride) return;
	NodeDataOverride = InNodeDataOverride;
}

const TArray<UClass*>& UXMSModularSpellsSubsystem::GetNodeClasses()
{
	return NodeClassCache.Classes;
}
