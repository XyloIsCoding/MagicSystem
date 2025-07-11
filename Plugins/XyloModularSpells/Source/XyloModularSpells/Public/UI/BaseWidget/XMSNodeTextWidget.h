// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XMSNodeTextWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FXMSNodeTextClickedSignature)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetDisplayText(const FString& InText, const FLinearColor& Color = FLinearColor::White);
protected:
	virtual void DisplayTextSet(const FString& InText, const FLinearColor& Color);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_DisplayTextSet(const FString& InText, const FLinearColor& Color);

public:
	FXMSNodeTextClickedSignature NodeTextClickedDelegate;
	UFUNCTION(BlueprintCallable)
	void BroadcastNodeTextClickedDelegate();
};
