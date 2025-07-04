// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/XMSNodeOptionsSelectionWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


void UXMSNodeOptionsSelectionWidget::SelectOption(int32 Index)
{
	OptionSelected(Index);
	BP_OptionSelected(Index);
	OptionSelectedDelegate.Broadcast(Index);
}

void UXMSNodeOptionsSelectionWidget::OptionSelected(int32 Index)
{
}

