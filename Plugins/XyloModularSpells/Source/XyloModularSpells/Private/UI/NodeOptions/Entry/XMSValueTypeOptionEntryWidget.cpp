// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/Entry/XMSValueTypeOptionEntryWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Components/RichTextBlock.h"
#include "Node/XMSNodeDataRegistry.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"
#include "UI/NodeTooltip/XMSNodeTooltipWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeTooltipInterface Interface
 */

void UXMSValueTypeOptionEntryWidget::InitializeTooltip(UXMSNodeTooltipWidget* TooltipWidget)
{
	Super::InitializeTooltip(TooltipWidget);

	if (!TooltipWidget) return;

	// Container tooltip
	if (FXMSValueTypeData* ValueTypeData = UXMSNodeStaticLibrary::GetValueTypeData(ValueType))
	{
		TooltipWidget->Title->SetText(ValueTypeData->Name);
		TooltipWidget->Body->SetText(ValueTypeData->Description);
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
