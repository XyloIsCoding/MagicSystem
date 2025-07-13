// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/Entry/XMSIntegerOptionEntryWidget.h"

#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSIntegerOptionEntryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (OptionText)
	{
		OptionText->NodeIconClickedDelegate.AddUObject(this, &UXMSIntegerOptionEntryWidget::BroadcastOptionSelectedDelegate);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionEntryWidget Interface
 */

void UXMSIntegerOptionEntryWidget::ClearDelegates()
{
	Super::ClearDelegates();
	IntegerOptionSelectedDelegate.Clear();
}

void UXMSIntegerOptionEntryWidget::InitializeOption(int32 InOptionIndex)
{
	Super::InitializeOption(InOptionIndex);
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

	OptionText->SetDisplayText(!DisplayOverride.IsEmpty() ? DisplayOverride : FString::FromInt(OptionValue));
}
