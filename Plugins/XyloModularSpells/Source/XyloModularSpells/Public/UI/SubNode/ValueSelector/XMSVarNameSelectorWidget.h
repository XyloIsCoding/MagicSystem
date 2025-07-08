// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubNode/XMSNodeValueSelectorWidget.h"
#include "XMSVarNameSelectorWidget.generated.h"

class UXMSVarNameOptionEntryWidget;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSVarNameSelectorWidget : public UXMSNodeValueSelectorWidget, public IXMSNodeOptionsInterface
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
	UFUNCTION(BlueprintCallable)
	void BroadcastOptionsRequestedDelegate();
	FXMSOptionsRequestedSignature OptionsRequestedDelegate;
	virtual FXMSOptionsRequestedSignature& GetOptionsRequestedDelegate() override { return OptionsRequestedDelegate; }
	virtual void InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSVarNameSelectorWidget
	 */

protected:
	virtual void ChangeVarName(const FString& InName);
	virtual void OnVarNameChanged(const FString& InName);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnVarNameChanged(const FString& InName);

protected:
	UPROPERTY(EditAnywhere, Category = "OptionWidget")
	TSubclassOf<UXMSVarNameOptionEntryWidget> VarNameOptionWidgetClass;
};
