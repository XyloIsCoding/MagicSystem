// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NodeOptions/XMSNodeOptionEntryWidget.h"
#include "XMSIntegerOptionEntryWidget.generated.h"

class UXMSNodeTextWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FXMSIntegerOptionSelectedSignature, int32)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSIntegerOptionEntryWidget : public UXMSNodeOptionEntryWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UUserWidget Interface
	 */
	
	virtual void NativeOnInitialized() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeOptionEntryWidget Interface
	 */
	
public:
	virtual void ClearDelegates() override;
	virtual void InitializeOption(int32 InOptionIndex) override;
	virtual void BroadcastOptionSelectedDelegate() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSIntegerOptionEntryWidget
	 */

public:
	FXMSIntegerOptionSelectedSignature IntegerOptionSelectedDelegate;
	void SetOptionValue(int32 InValue, const FString& DisplayOverride = FString());
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeTextWidget> OptionText;
	int32 OptionValue;
};
