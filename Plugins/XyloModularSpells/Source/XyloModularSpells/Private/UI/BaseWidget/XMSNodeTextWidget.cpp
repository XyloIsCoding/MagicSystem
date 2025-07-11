// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget/XMSNodeTextWidget.h"

void UXMSNodeTextWidget::SetDisplayText(const FString& InText, const FLinearColor& Color)
{
	DisplayTextSet(InText, Color);
	BP_DisplayTextSet(InText, Color);
}

void UXMSNodeTextWidget::DisplayTextSet(const FString& InText, const FLinearColor& Color)
{
}

void UXMSNodeTextWidget::BroadcastNodeTextClickedDelegate()
{
	NodeTextClickedDelegate.Broadcast();
}
