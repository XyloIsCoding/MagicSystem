// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XMSNodeIconWidget.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeIconWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetDisplayName(const FString& ClassName);
protected:
	virtual void DisplayNameSet(const FString& ClassName);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_DisplayNameSet(const FString& ClassName);

public:
	void SetDisplayIcon(UTexture2D* Icon);
protected:
	virtual void DisplayIconSet(UTexture2D* Icon);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_DisplayIconSet(UTexture2D* Icon);
};
