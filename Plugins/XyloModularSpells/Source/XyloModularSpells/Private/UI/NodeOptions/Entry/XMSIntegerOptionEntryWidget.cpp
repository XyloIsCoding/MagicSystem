// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/Entry/XMSIntegerOptionEntryWidget.h"

#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionEntryWidget Interface
 */

void UXMSIntegerOptionEntryWidget::ClearDelegates()
{
	Super::ClearDelegates();
	IntegerOptionSelectedDelegate.Clear();
}

void UXMSIntegerOptionEntryWidget::BroadcastOptionSelectedDelegate()
{
	IntegerOptionSelectedDelegate.Broadcast(OptionValue);
	Super::BroadcastOptionSelectedDelegate();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSIntegerOptionEntryWidget
 */

void UXMSIntegerOptionEntryWidget::SetOptionValue(int32 InValue, const FString& DisplayOverride)
{
	OptionValue = InValue;

	OptionDisplayWidget->SetDisplayText(!DisplayOverride.IsEmpty() ? DisplayOverride : FString::FromInt(OptionValue));
}
