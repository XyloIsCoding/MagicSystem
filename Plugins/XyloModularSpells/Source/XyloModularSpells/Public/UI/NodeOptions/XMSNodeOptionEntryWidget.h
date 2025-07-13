// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XMSNodeOptionEntryWidget.generated.h"

class UXMSNodeIconWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FXMSNodeOptionEntrySelectedSignature, int32)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeOptionEntryWidget : public UUserWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UUserWidget Interface
	 */
	
	virtual void NativeOnInitialized() override;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeOptionEntryWidget
	 */

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeIconWidget> OptionDisplayWidget;
	
public:
	FXMSNodeOptionEntrySelectedSignature NodeOptionEntrySelectedDelegate;
	/** Broadcasts NodeOptionEntrySelectedDelegate. Should be overridden to also broadcast sub-class-specific
	 * selection delegates */
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastOptionSelectedDelegate();
	/** called by UXMSNodeOptionsSelectionWidget::InitializeOptions
	 * It is used to clear every delegate to allow for reusing this widget */
	virtual void ClearDelegates();
	/** called by UXMSNodeOptionsSelectionWidget::InitializeOptions
	 * Initialize this widget */
	virtual void InitializeOption(int32 InOptionIndex);
protected:
	int32 OptionIndex = 0;
};
