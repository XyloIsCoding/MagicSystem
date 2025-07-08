// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XMSNodeIconWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FXMSNodeIconClickedSignature)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeIconWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetDisplayName(const FString& InName);
protected:
	virtual void DisplayNameSet(const FString& InName);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_DisplayNameSet(const FString& InName);

public:
	UFUNCTION(BlueprintCallable)
	void SetDisplayIcon(UTexture2D* Icon);
protected:
	virtual void DisplayIconSet(UTexture2D* Icon);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_DisplayIconSet(UTexture2D* Icon);

public:
	FXMSNodeIconClickedSignature NodeIconClickedDelegate;
	UFUNCTION(BlueprintCallable)
	void BroadcastNodeIconClickedDelegate();
};
