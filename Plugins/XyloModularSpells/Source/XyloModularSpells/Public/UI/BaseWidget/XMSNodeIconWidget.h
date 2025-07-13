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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeIconWidget
	 */

/*--------------------------------------------------------------------------------------------------------------------*/
	// Icon
	
public:
	UFUNCTION(BlueprintCallable)
	void SetDisplayIconName(const FString& InName);
protected:
	virtual void DisplayIconNameSet(const FString& InName);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_DisplayIconNameSet(const FString& InName);

public:
	UFUNCTION(BlueprintCallable)
	void SetDisplayIcon(UTexture2D* Icon);
protected:
	virtual void DisplayIconSet(UTexture2D* Icon);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_DisplayIconSet(UTexture2D* Icon);

	// ~Icon
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// Text
	
public:
	UFUNCTION(BlueprintCallable)
	void SetDisplayText(const FString& InText, const FLinearColor& Color = FLinearColor::White);
protected:
	virtual void DisplayTextSet(const FString& InText, const FLinearColor& Color);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_DisplayTextSet(const FString& InText, const FLinearColor& Color);

	// ~Text
/*--------------------------------------------------------------------------------------------------------------------*/

public:
	FXMSNodeIconClickedSignature NodeIconClickedDelegate;
	UFUNCTION(BlueprintCallable)
	void BroadcastNodeIconClickedDelegate();
};
