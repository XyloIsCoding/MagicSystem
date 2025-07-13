// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/XMSNodeOptionEntryWidget.h"

#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSNodeOptionEntryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (OptionDisplayWidget)
	{
		OptionDisplayWidget->NodeIconClickedDelegate.AddUObject(this, &UXMSNodeOptionEntryWidget::BroadcastOptionSelectedDelegate);
		OptionDisplayWidget->NodeIconHoveredDelegate.AddUObject(this, &UXMSNodeOptionEntryWidget::BroadcastTooltipRequestedDelegate);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeTooltipInterface Interface
 */

void UXMSNodeOptionEntryWidget::BroadcastTooltipRequestedDelegate()
{
	TooltipRequestedDelegate.Broadcast(this);
}

void UXMSNodeOptionEntryWidget::InitializeTooltip(UXMSNodeTooltipWidget* TooltipWidget)
{
	// Implement in child classes to initialize the tooltip with information about this entry
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionEntryWidget
 */

void UXMSNodeOptionEntryWidget::BroadcastOptionSelectedDelegate()
{
	NodeOptionEntrySelectedDelegate.Broadcast(OptionIndex);
}

void UXMSNodeOptionEntryWidget::ClearDelegates()
{
	NodeOptionEntrySelectedDelegate.Clear();
}

void UXMSNodeOptionEntryWidget::InitializeOption(int32 InOptionIndex)
{
	OptionIndex = InOptionIndex;
}
