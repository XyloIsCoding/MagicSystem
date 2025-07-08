// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget/XMSNodeTextWidget.h"

void UXMSNodeTextWidget::SetDisplayText(const FString& InText)
{
	DisplayTextSet(InText);
	BP_DisplayTextSet(InText);
}

void UXMSNodeTextWidget::DisplayTextSet(const FString& InText)
{
}

void UXMSNodeTextWidget::BroadcastNodeTextClickedDelegate()
{
	NodeTextClickedDelegate.Broadcast();
}
