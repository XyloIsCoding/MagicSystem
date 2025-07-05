// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeCanvasEntryWidget.h"
#include "XMSArrayAddButtonWidget.generated.h"

class UXMSNodeIconWidget;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSArrayAddButtonWidget : public UXMSNodeCanvasEntryWidget
{
	GENERATED_BODY()

public:
	UXMSArrayAddButtonWidget();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UUserWidget Interface
	 */
	
	virtual void NativeOnInitialized() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSArrayAddButtonWidget
	 */

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeIconWidget> Icon;

protected:
	UFUNCTION(BlueprintCallable)
	void AddSubNode();
	
};
