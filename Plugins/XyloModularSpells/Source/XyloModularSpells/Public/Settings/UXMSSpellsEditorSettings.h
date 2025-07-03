// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UXMSSpellsEditorSettings.generated.h"

class UXMSNodeDataRegistry;

/**
 * 
 */
UCLASS(config=Game, DefaultConfig)
class XYLOMODULARSPELLS_API UUXMSSpellsEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UUXMSSpellsEditorSettings(const FObjectInitializer& ObjectInitializer);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UDeveloperSettings Interface
	 */
	
public:
	virtual FName GetCategoryName() const override;
	
#if WITH_EDITOR
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UUXMSSpellsEditorSettings
	 */

public:
	UPROPERTY(Config, EditAnywhere, Category="Editor")
	TSoftObjectPtr<UXMSNodeDataRegistry> NodeDataRegistry;
	
};
