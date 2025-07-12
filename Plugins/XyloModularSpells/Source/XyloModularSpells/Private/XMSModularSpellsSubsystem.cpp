// Fill out your copyright notice in the Description page of Project Settings.


#include "XMSModularSpellsSubsystem.h"

#include "Node/XMSNodeDataRegistry.h"
#include "Node/Base/XMSNode.h"
#include "Settings/UXMSSpellsEditorSettings.h"


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
		return Class->HasAnyClassFlags(CLASS_Abstract) || !Class->HasAnyClassFlags(CLASS_Native);
	});

	Classes.Append(FoundClasses);
	Classes.Sort([](const UClass& A, const UClass& B) { return A.GetName().ToLower() > B.GetName().ToLower(); });
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



UXMSModularSpellsSubsystem* UXMSModularSpellsSubsystem::Get()
{
	if (!GEngine) return nullptr;
	return GEngine->GetEngineSubsystem<UXMSModularSpellsSubsystem>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UEngineSubsystem Interface
 */

void UXMSModularSpellsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	NodeClassCache.InitForType(UXMSNode::StaticClass());
	RegisterNodeDataRegistry();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSModularSpellsSubsystem
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// NodeDataRegistry

void UXMSModularSpellsSubsystem::RegisterNodeDataRegistry()
{
	if (const UUXMSSpellsEditorSettings* Settings = GetMutableDefault<UUXMSSpellsEditorSettings>())
	{
		NodeDataRegistry = Settings->NodeDataRegistry.LoadSynchronous();
		if (NodeDataRegistry)
		{
			UE_LOG(LogTemp, Warning, TEXT("UXMSModularSpellsSubsystem::RegisterNodeDataRegistry >> success"))
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UXMSModularSpellsSubsystem::RegisterNodeDataRegistry >> failed"))
		}
	}
}

// ~NodeDataRegistry
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// NodeClasses

const TArray<UClass*>& UXMSModularSpellsSubsystem::GetNativeNodeClasses()
{
	return NodeClassCache.Classes;
}

// ~NodeClasses
/*--------------------------------------------------------------------------------------------------------------------*/

