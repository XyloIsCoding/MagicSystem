// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XMSNodeOptionEntryWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FXMSNodeOptionEntrySelectedSignature, int32)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeOptionEntryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void InitializeOption(int32 InOptionIndex);
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastOptionSelectedDelegate();
	FXMSNodeOptionEntrySelectedSignature NodeOptionEntrySelectedDelegate;
protected:
	int32 OptionIndex = 0;
};
