// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget/XMSNodeIconWidget.h"

void UXMSNodeIconWidget::SetDisplayName(const FString& InName)
{
	DisplayNameSet(InName);
	BP_DisplayNameSet(InName);
}

void UXMSNodeIconWidget::DisplayNameSet(const FString& InName)
{
}

void UXMSNodeIconWidget::SetDisplayIcon(UTexture2D* Icon)
{
	DisplayIconSet(Icon);
	BP_DisplayIconSet(Icon);
}

void UXMSNodeIconWidget::DisplayIconSet(UTexture2D* Icon)
{
}

void UXMSNodeIconWidget::BroadcastNodeIconClickedDelegate()
{
	NodeIconClickedDelegate.Broadcast();
}
