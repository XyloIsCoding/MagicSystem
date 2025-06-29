// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeClassOptionsWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


void UXMSNodeClassOptionsWidget::UpdateClassIcon(UXMSNodeIconWidget* IconWidget, UClass* NodeClass)
{
	if (!IconWidget || !NodeClass) return;

	if (UTexture2D* Icon = UXMSNodeStaticLibrary::GetNodeClassIcon(NodeClass))
	{
		IconWidget->SetDisplayIcon(Icon);
	}
	else
	{
		IconWidget->SetDisplayName(UXMSNodeStaticLibrary::GetNodeClassName(NodeClass));
	}
}

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
