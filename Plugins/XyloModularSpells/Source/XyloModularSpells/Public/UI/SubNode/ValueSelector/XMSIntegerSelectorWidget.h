// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubNode/XMSNodeValueOptionSelectorWidget.h"
#include "UI/SubNode/XMSNodeValueSelectorWidget.h"
#include "XMSIntegerSelectorWidget.generated.h"

class UXMSIntegerOptionEntryWidget;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSIntegerSelectorWidget : public UXMSNodeValueOptionSelectorWidget
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
	 * UXMSStringSelectorWidget
	 */

protected:
	virtual void SelectionCompleted(bool bSuccess);
	virtual void AppendDigit(int32 InDigit);
	void OnOwningNodeIntegerValueChanged(int32 NewNumber, int32 OldNumber);
	virtual void OnNumberChanged(int32 InNumber);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnNumberChanged(int32 InNumber);
protected:
	int32 CachedNumber;
	
protected:
	UPROPERTY(EditAnywhere, Category = "OptionWidget")
	TSubclassOf<UXMSIntegerOptionEntryWidget> NumberOptionWidgetClass;
};
