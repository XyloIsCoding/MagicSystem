// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "XMSNodeOptionEntryWidget.h"
#include "XMSVarTypeOptionEntryWidget.generated.h"

class UXMSNodeIconWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FXMSVarTypeOptionSelectedSignature, const FGameplayTag&)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSVarTypeOptionEntryWidget : public UXMSNodeOptionEntryWidget
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
	virtual void InitializeOption(int32 InOptionIndex) override;
	virtual void BroadcastOptionSelectedDelegate() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSVarTypeOptionEntryWidget
	 */

public:
	FXMSVarTypeOptionSelectedSignature VarTypeOptionSelectedDelegate;
	void SetValueType(const FGameplayTag& InValueType);
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeIconWidget> ValueTypeIcon;
	FGameplayTag ValueType;
};
