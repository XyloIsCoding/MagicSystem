// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubNode/XMSNodeValueSelectorWidget.h"
#include "XMSValueTypeSelectorWidget.generated.h"

class UXMSValueTypeOptionEntryWidget;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSValueTypeSelectorWidget : public UXMSNodeValueSelectorWidget, public IXMSNodeOptionsInterface
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UUserWidget Interface
	 */
	
	virtual void NativeOnInitialized() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeCanvasEntryWidget
	 */

public:
	virtual void OnOwningNodeSet() override;
	
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
	 * UXMSValueTypeSelectorWidget
	 */

protected:
	virtual void ChangeValueType(const FGameplayTag& InType);
	virtual void OnValueTypeChanged(const FGameplayTag& NewType);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnValueTypeChanged(const FGameplayTag& NewType);
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeIconWidget> ValueTypeIcon;
	UPROPERTY(EditAnywhere, Category = "OptionWidget")
	TSubclassOf<UXMSValueTypeOptionEntryWidget> ValueTypeOptionWidgetClass;
};
