// Fill out your copyright notice in the Description page of Project Settings.


#include "XMSModularSpellsSubsystem.h"
#include "Node/Base/XMSNode.h"


void FXMSNodeClassCache::InitForType(UClass* InClass)
{
	Classes.Empty();

	if (!InClass)
	{
		return;
	}

	TArray<UClass*> FoundClasses;
	GetDerivedClasses(InClass, FoundClasses, true);
	FoundClasses.RemoveAll([](UClass* Class) {
		return Class->HasAnyClassFlags(CLASS_Abstract);
	});

	Classes.Append(FoundClasses);
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

void UXMSModularSpellsSubsystem::RegisterNodeDataRegistry(UXMSNodeDataRegistry* InNodeDataRegistry)
{
	if (!InNodeDataRegistry) return;
	NodeDataRegistry = InNodeDataRegistry;
}

const TArray<UClass*>& UXMSModularSpellsSubsystem::GetNodeClasses()
{
	return NodeClassCache.Classes;
}
