// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/Entry/XMSValueTypeOptionEntryWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSValueTypeOptionEntryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ValueTypeIcon)
	{
		ValueTypeIcon->NodeIconClickedDelegate.AddUObject(this, &UXMSValueTypeOptionEntryWidget::BroadcastOptionSelectedDelegate);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionEntryWidget Interface
 */

void UXMSValueTypeOptionEntryWidget::ClearDelegates()
{
	Super::ClearDelegates();
	ValueTypeOptionSelectedDelegate.Clear();
}

void UXMSValueTypeOptionEntryWidget::InitializeOption(int32 InOptionIndex)
{
	Super::InitializeOption(InOptionIndex);
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
		ValueTypeIcon->SetDisplayIcon(Icon);
	}
	else
	{
		ValueTypeIcon->SetDisplayName(ValueType.ToString());
	}
}
