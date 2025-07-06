// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubNode/XMSNodeValueSelectorWidget.h"
#include "XMSVarTypeSelectorWidget.generated.h"

class UXMSVarTypeOptionEntryWidget;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSVarTypeSelectorWidget : public UXMSNodeValueSelectorWidget, public IXMSNodeOptionsInterface
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSNodeOptionsInterface Interface
	 */

public:
	FXMSOptionsRequestedSignature OptionsRequestedDelegate;
	virtual FXMSOptionsRequestedSignature& GetOptionsRequestedDelegate() override { return OptionsRequestedDelegate; }
	virtual void InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSVarTypeSelectorWidget
	 */

protected:
	virtual void ChangeValueType(const FGameplayTag& InType);
	
protected:
	UPROPERTY(EditAnywhere, Category = "OptionWidget")
	TSubclassOf<UXMSVarTypeOptionEntryWidget> ValueTypeOptionWidgetClass;
};
