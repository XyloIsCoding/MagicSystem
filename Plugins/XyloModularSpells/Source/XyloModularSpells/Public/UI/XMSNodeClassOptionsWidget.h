// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeEditorWidget.h"
#include "XMSNodeClassOptionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeClassOptionsWidget : public UXMSNodeEditorWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeClassOptionsWidget
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
