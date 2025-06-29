// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget/XMSNodeIconWidget.h"

void UXMSNodeIconWidget::SetDisplayName(const FString& ClassName)
{
	DisplayNameSet(ClassName);
	BP_DisplayNameSet(ClassName);
}

void UXMSNodeIconWidget::DisplayNameSet(const FString& ClassName)
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
