// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/XMSNodeOptionsSelectionWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"
#include "UI/NodeTooltip/XMSNodeTooltipWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionsSelectionWidget
 */

void UXMSNodeOptionsSelectionWidget::PrepareOptionEntryWidget(UXMSNodeOptionEntryWidget* OptionEntryWidget, int32 Index)
{
	OptionEntryWidget->ClearDelegates();
	OptionEntryWidget->InitializeOption(Index);
	OptionEntryWidget->NodeOptionEntrySelectedDelegate.AddUObject(this, &ThisClass::SelectOption);
	OptionEntryWidget->GetTooltipRequestedDelegate().AddUObject(this, &ThisClass::TooltipRequested);
}

void UXMSNodeOptionsSelectionWidget::OnOptionsInitialized()
{
}

/*--------------------------------------------------------------------------------------------------------------------*/
// OptionSelection

void UXMSNodeOptionsSelectionWidget::ClearDelegates()
{
	OptionSelectedDelegate.Clear();
	SelectionCompletedDelegate.Clear();
}

void UXMSNodeOptionsSelectionWidget::SelectOption(int32 Index)
{
	OptionSelected(Index);
	BP_OptionSelected(Index);
	OptionSelectedDelegate.Broadcast(Index);

	if (bSingleChoice)
	{
		BroadcastSelectionCompleted(true);
	}
}

void UXMSNodeOptionsSelectionWidget::OptionSelected(int32 Index)
{
}

void UXMSNodeOptionsSelectionWidget::BroadcastSelectionCompleted(bool bSuccess)
{
	SelectionCompleted(bSuccess);
	BP_SelectionCompleted(bSuccess);
	SelectionCompletedDelegate.Broadcast(bSuccess);
}

void UXMSNodeOptionsSelectionWidget::SelectionCompleted(bool bSuccess)
{
}

// ~OptionSelection
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// Tooltip

void UXMSNodeOptionsSelectionWidget::TooltipRequested(UWidget* Widget)
{
	IXMSNodeTooltipInterface* TooltipInterface = Cast<IXMSNodeTooltipInterface>(Widget);
	if (!TooltipInterface) return;

	OptionTooltipWidget->ClearTooltip();
	TooltipInterface->InitializeTooltip(OptionTooltipWidget);
}

// ~Tooltip
/*--------------------------------------------------------------------------------------------------------------------*/

