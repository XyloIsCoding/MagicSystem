// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NodeOptions/XMSNodeOptionEntryWidget.h"
#include "XMSStringOptionEntryWidget.generated.h"

class UXMSNodeIconWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FXMSStringOptionSelectedSignature, const FString&)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSStringOptionEntryWidget : public UXMSNodeOptionEntryWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeOptionEntryWidget Interface
	 */
	
public:
	virtual void ClearDelegates() override;
	virtual void BroadcastOptionSelectedDelegate() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSStringOptionEntryWidget
	 */

public:
	FXMSStringOptionSelectedSignature StringOptionSelectedDelegate;
	void SetOptionName(const FString& InVarName);
protected:
	FString OptionString;
};
