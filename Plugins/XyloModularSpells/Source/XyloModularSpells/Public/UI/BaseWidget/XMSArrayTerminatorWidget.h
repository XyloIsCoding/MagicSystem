// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeCanvasEntryWidget.h"
#include "XMSArrayTerminatorWidget.generated.h"

class UXMSNodeIconWidget;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSArrayTerminatorWidget : public UXMSNodeCanvasEntryWidget
{
	GENERATED_BODY()

public:
	UXMSArrayTerminatorWidget();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UUserWidget Interface
	 */
	
	virtual void NativeOnInitialized() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSArrayTerminatorWidget
	 */

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeIconWidget> Icon;

protected:
	UFUNCTION(BlueprintCallable)
	void AddSubNode();
	
};
