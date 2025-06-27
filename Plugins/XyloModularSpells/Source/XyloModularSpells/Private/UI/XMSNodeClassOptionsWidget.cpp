// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeClassOptionsWidget.h"

void UXMSNodeClassOptionsWidget::SetOptions(const TArray<UClass*>& InOptions)
{
	Options = InOptions;
	OptionsSet();
	BP_OptionsSet();
}

void UXMSNodeClassOptionsWidget::OptionsSet()
{
}
