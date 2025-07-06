// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/XMSVarTypeOptionEntryWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSVarTypeOptionEntryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ValueTypeIcon)
	{
		ValueTypeIcon->NodeIconClickedDelegate.AddUObject(this, &UXMSVarTypeOptionEntryWidget::BroadcastOptionSelectedDelegate);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionEntryWidget Interface
 */

void UXMSVarTypeOptionEntryWidget::InitializeOption(int32 InOptionIndex)
{
	Super::InitializeOption(InOptionIndex);
	VarTypeOptionSelectedDelegate.Clear();
}

void UXMSVarTypeOptionEntryWidget::BroadcastOptionSelectedDelegate()
{
	VarTypeOptionSelectedDelegate.Broadcast(ValueType);
	Super::BroadcastOptionSelectedDelegate();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSVarTypeOptionEntryWidget
 */

void UXMSVarTypeOptionEntryWidget::SetValueType(const FGameplayTag& InValueType)
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
