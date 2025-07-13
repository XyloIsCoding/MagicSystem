// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubNode/XMSNodeValueOptionSelectorWidget.h"
#include "UI/SubNode/XMSNodeValueSelectorWidget.h"
#include "XMSVarNameSelectorWidget.generated.h"

class UXMSStringOptionEntryWidget;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSVarNameSelectorWidget : public UXMSNodeValueOptionSelectorWidget
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
	 * UXMSVarNameSelectorWidget
	 */

protected:
	virtual void ChangeVarName(const FString& InName);
	void OnOwningNodeVarNameChanged(const FString& NewName, const FString& OldName, bool bValidName);
	virtual void OnVarNameChanged(const FString& InName, bool bValidName);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnVarNameChanged(const FString& InName, bool bValidName);

protected:
	UPROPERTY(EditAnywhere, Category = "OptionWidget")
	TSubclassOf<UXMSStringOptionEntryWidget> VarNameOptionWidgetClass;
};
