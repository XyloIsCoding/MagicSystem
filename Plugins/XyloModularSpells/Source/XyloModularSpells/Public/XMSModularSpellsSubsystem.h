// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "XMSModularSpellsSubsystem.generated.h"

class UXMSNodeDataOverride;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSModularSpellsSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	void RegisterNodeDataOverride(UXMSNodeDataOverride* InNodeDataOverride);
private:
	UPROPERTY()
	TObjectPtr<UXMSNodeDataOverride> NodeDataOverride;
};
