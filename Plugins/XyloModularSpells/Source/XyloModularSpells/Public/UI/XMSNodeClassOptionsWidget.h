// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XMSNodeClassOptionsWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FXMSClassOptionChosenSignature, UClass*)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeClassOptionsWidget : public UUserWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeClassOptionsWidget
	 */

public:
	FXMSClassOptionChosenSignature ClassOptionChosenDelegate;
	UFUNCTION(BlueprintCallable)
	void SelectOption(int32 Index);
protected:
	virtual void OptionSelected();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OptionSelected();

public:
	void SetOptions(const TArray<UClass*>& InOptions);
protected:
	virtual void OptionsSet();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OptionsSet();
	UPROPERTY(BlueprintReadOnly)
	TArray<UClass*> Options;
	
};
