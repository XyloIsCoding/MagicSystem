// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/Entry/XMSStringOptionEntryWidget.h"

#include "UI/BaseWidget/XMSNodeIconWidget.h"
#include "UI/BaseWidget/XMSNodeTextWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSStringOptionEntryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (OptionText)
	{
		OptionText->NodeTextClickedDelegate.AddUObject(this, &UXMSStringOptionEntryWidget::BroadcastOptionSelectedDelegate);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionEntryWidget Interface
 */

void UXMSStringOptionEntryWidget::ClearDelegates()
{
	Super::ClearDelegates();
	StringOptionSelectedDelegate.Clear();
}

void UXMSStringOptionEntryWidget::InitializeOption(int32 InOptionIndex)
{
	Super::InitializeOption(InOptionIndex);
}

void UXMSStringOptionEntryWidget::BroadcastOptionSelectedDelegate()
{
	StringOptionSelectedDelegate.Broadcast(OptionString);
	Super::BroadcastOptionSelectedDelegate();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSStringOptionEntryWidget
 */

void UXMSStringOptionEntryWidget::SetOptionName(const FString& InVarName)
{
	OptionString = InVarName;

	OptionText->SetDisplayText(OptionString);
}
