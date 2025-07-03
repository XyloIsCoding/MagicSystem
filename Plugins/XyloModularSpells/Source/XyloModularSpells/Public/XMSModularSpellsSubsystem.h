// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "XMSModularSpellsSubsystem.generated.h"

class UGameEngine;
class UXMSNodeDataRegistry;

/**
 * Collects all node classes (same concept as FNetSerializeScriptStructCache)
 */
USTRUCT()
struct FXMSNodeClassCache
{
	GENERATED_BODY()

	void InitForType(UClass* InClass);

	UPROPERTY()
	TArray<TObjectPtr<UClass>> Classes;
};


/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSModularSpellsSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	static UXMSModularSpellsSubsystem* Get();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	void RegisterNodeDataRegistry();
	UXMSNodeDataRegistry* GetNodeDataRegistry() const { return NodeDataRegistry; }
private:
	UPROPERTY()
	TObjectPtr<UXMSNodeDataRegistry> NodeDataRegistry;

public:
	const TArray<UClass*>& GetNodeClasses();
private:
	FXMSNodeClassCache NodeClassCache;
};
