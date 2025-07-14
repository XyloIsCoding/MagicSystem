// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/NodeOptions/XMSNodeOptionEntryWidget.h"
#include "XMSValueTypeOptionEntryWidget.generated.h"

class UXMSNodeIconWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FXMSValueTypeOptionSelectedSignature, const FGameplayTag&)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSValueTypeOptionEntryWidget : public UXMSNodeOptionEntryWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSNodeTooltipInterface Interface
	 */

public:
	virtual void InitializeTooltip(UXMSNodeTooltipWidget* TooltipWidget) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeOptionEntryWidget Interface
	 */
	
public:
	virtual void ClearDelegates() override;
	virtual void BroadcastOptionSelectedDelegate() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSValueTypeOptionEntryWidget
	 */

public:
	FXMSValueTypeOptionSelectedSignature ValueTypeOptionSelectedDelegate;
	void SetValueType(const FGameplayTag& InValueType);
protected:
	FGameplayTag ValueType;
};
