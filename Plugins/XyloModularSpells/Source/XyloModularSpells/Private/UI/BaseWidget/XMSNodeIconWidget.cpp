// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeIconWidget
	 */

/*--------------------------------------------------------------------------------------------------------------------*/
	// Icon

void UXMSNodeIconWidget::SetDisplayIconName(const FString& InName)
{
	DisplayIconNameSet(InName);
	BP_DisplayIconNameSet(InName);
}

void UXMSNodeIconWidget::DisplayIconNameSet(const FString& InName)
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

// ~Icon
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// Text

void UXMSNodeIconWidget::SetDisplayText(const FString& InText, const FLinearColor& Color)
{
	DisplayTextSet(InText, Color);
	BP_DisplayTextSet(InText, Color);
}

void UXMSNodeIconWidget::DisplayTextSet(const FString& InText, const FLinearColor& Color)
{
}

// ~Text
/*--------------------------------------------------------------------------------------------------------------------*/

void UXMSNodeIconWidget::BroadcastNodeIconClickedDelegate()
{
	NodeIconClickedDelegate.Broadcast();
}
