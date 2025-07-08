// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/XMSNodeOptionsSelectionWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionsSelectionWidget
 */

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
		BroadcastSelectionCompleted();
	}
}

void UXMSNodeOptionsSelectionWidget::OptionSelected(int32 Index)
{
}

void UXMSNodeOptionsSelectionWidget::BroadcastSelectionCompleted()
{
	SelectionCompleted();
	BP_SelectionCompleted();
	SelectionCompletedDelegate.Broadcast();
}

void UXMSNodeOptionsSelectionWidget::SelectionCompleted()
{
}

// ~OptionSelection
/*--------------------------------------------------------------------------------------------------------------------*/
