// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubNode/XMSNodeValueOptionSelectorWidget.h"
#include "UI/SubNode/XMSNodeValueSelectorWidget.h"
#include "XMSValueTypeSelectorWidget.generated.h"

class UXMSValueTypeOptionEntryWidget;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSValueTypeSelectorWidget : public UXMSNodeValueOptionSelectorWidget
{
	GENERATED_BODY()
	
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
	virtual void InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSValueTypeSelectorWidget
	 */

protected:
	virtual void ChangeValueType(const FGameplayTag& InType);
	void OnOwningNodeValueTypeChanged(const FGameplayTag& NewType, const FGameplayTag& OldType);
	virtual void OnValueTypeChanged(const FGameplayTag& NewType);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnValueTypeChanged(const FGameplayTag& NewType);
	
protected:
	UPROPERTY(EditAnywhere, Category = "OptionWidget")
	TSubclassOf<UXMSValueTypeOptionEntryWidget> ValueTypeOptionWidgetClass;
};
