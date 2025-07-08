// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NodeOptions/XMSNodeOptionEntryWidget.h"
#include "XMSVarNameOptionEntryWidget.generated.h"

class UXMSNodeTextWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FXMSVarNameOptionSelectedSignature, const FString&)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSVarNameOptionEntryWidget : public UXMSNodeOptionEntryWidget
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
	 * UXMSVarNameOptionEntryWidget
	 */

public:
	FXMSVarNameOptionSelectedSignature VarNameOptionSelectedDelegate;
	void SetVarName(const FString& InVarName);
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeTextWidget> VarNameText;
	FString VarName;
};
