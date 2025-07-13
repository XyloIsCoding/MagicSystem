// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/Entry/XMSValueTypeOptionEntryWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionEntryWidget Interface
 */

void UXMSValueTypeOptionEntryWidget::ClearDelegates()
{
	Super::ClearDelegates();
	ValueTypeOptionSelectedDelegate.Clear();
}

void UXMSValueTypeOptionEntryWidget::BroadcastOptionSelectedDelegate()
{
	ValueTypeOptionSelectedDelegate.Broadcast(ValueType);
	Super::BroadcastOptionSelectedDelegate();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSValueTypeOptionEntryWidget
 */

void UXMSValueTypeOptionEntryWidget::SetValueType(const FGameplayTag& InValueType)
{
	ValueType = InValueType;

	if (UTexture2D* Icon = UXMSNodeStaticLibrary::GetValueTypeIcon(ValueType))
	{
		OptionDisplayWidget->SetDisplayIcon(Icon);
	}
	else
	{
		OptionDisplayWidget->SetDisplayIconName(ValueType.ToString());
	}
}
