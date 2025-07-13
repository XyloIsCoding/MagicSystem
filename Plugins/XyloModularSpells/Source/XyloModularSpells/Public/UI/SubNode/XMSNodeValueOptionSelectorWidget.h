// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeValueSelectorWidget.h"
#include "XMSNodeValueOptionSelectorWidget.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeValueOptionSelectorWidget : public UXMSNodeValueSelectorWidget, public IXMSNodeOptionsInterface
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UUserWidget Interface
	 */

public:
	virtual void NativeOnInitialized() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSNodeOptionsInterface Interface
	 */

public:
	UFUNCTION(BlueprintCallable)
	void BroadcastOptionsRequestedDelegate();
	FXMSOptionsRequestedSignature OptionsRequestedDelegate;
	virtual FXMSOptionsRequestedSignature& GetOptionsRequestedDelegate() override { return OptionsRequestedDelegate; }
	virtual void InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeValueOptionSelectorWidget
	 */

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeIconWidget> SelectorDisplayWidget;
};
