// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeEditorWidget.h"
#include "XMSNodeClassOptions.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeClassOptions : public UXMSNodeEditorWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeClassOptions
	 */

public:
	void SetOptions(const TArray<UClass*>& InOptions);
protected:
	virtual void OptionsSet();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OptionsSet();
	UPROPERTY(BlueprintReadOnly)
	TArray<UClass*> Options;
	
};
