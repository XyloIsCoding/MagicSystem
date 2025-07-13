// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/Entry/XMSStringOptionEntryWidget.h"

#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionEntryWidget Interface
 */

void UXMSStringOptionEntryWidget::ClearDelegates()
{
	Super::ClearDelegates();
	StringOptionSelectedDelegate.Clear();
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

	OptionDisplayWidget->SetDisplayText(OptionString);
}
