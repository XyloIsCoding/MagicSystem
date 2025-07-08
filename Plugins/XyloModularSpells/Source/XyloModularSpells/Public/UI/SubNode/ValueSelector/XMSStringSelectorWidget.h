// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SubNode/XMSNodeValueSelectorWidget.h"
#include "XMSStringSelectorWidget.generated.h"

class UXMSNodeTextWidget;
class UXMSStringOptionEntryWidget;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSStringSelectorWidget : public UXMSNodeValueSelectorWidget, public IXMSNodeOptionsInterface
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
	 * UXMSStringSelectorWidget
	 */

protected:
	virtual void AppendString(const FString& InString);
	void OnOwningNodeStringValueChanged(const FString& NewString, const FString& OldString);
	virtual void OnStringChanged(const FString& InString);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnStringChanged(const FString& InString);
	
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeTextWidget> StringText;
	UPROPERTY(EditAnywhere, Category = "OptionWidget")
	TSubclassOf<UXMSStringOptionEntryWidget> StringOptionWidgetClass;
};


