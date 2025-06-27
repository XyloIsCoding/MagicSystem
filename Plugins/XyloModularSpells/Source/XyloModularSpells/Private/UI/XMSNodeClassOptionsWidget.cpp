// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeClassOptionsWidget.h"


void UXMSNodeClassOptionsWidget::SelectOption(int32 Index)
{
	OptionSelected();
	BP_OptionSelected();
	ClassOptionChosenDelegate.Broadcast(Options.IsValidIndex(Index) ? Options[Index] : nullptr);
}

void UXMSNodeClassOptionsWidget::OptionSelected()
{
}

void UXMSNodeClassOptionsWidget::SetOptions(const TArray<UClass*>& InOptions)
{
	Options = InOptions;
	OptionsSet();
	BP_OptionsSet();
}

void UXMSNodeClassOptionsWidget::OptionsSet()
{
}
