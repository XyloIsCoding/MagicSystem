// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/XMSNodeOptionEntryWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionEntryWidget
 */

void UXMSNodeOptionEntryWidget::ClearDelegates()
{
	NodeOptionEntrySelectedDelegate.Clear();
}

void UXMSNodeOptionEntryWidget::InitializeOption(int32 InOptionIndex)
{
	OptionIndex = InOptionIndex;
}

void UXMSNodeOptionEntryWidget::BroadcastOptionSelectedDelegate()
{
	NodeOptionEntrySelectedDelegate.Broadcast(OptionIndex);
}
