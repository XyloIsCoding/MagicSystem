// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubNode/XMSNodeValueOptionSelectorWidget.h"
#include "UI/SubNode/XMSNodeValueSelectorWidget.h"
#include "XMSStringSelectorWidget.generated.h"

class UXMSStringOptionEntryWidget;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSStringSelectorWidget : public UXMSNodeValueOptionSelectorWidget
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
	virtual void AppendString(const FString& InString);
	void OnOwningNodeStringValueChanged(const FString& NewString, const FString& OldString);
	virtual void OnStringChanged(const FString& InString);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnStringChanged(const FString& InString);
protected:
	FString CachedString;
	
protected:
	UPROPERTY(EditAnywhere, Category = "OptionWidget")
	TSubclassOf<UXMSStringOptionEntryWidget> StringOptionWidgetClass;
};


