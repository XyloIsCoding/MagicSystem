// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/Entry/XMSVarNameOptionEntryWidget.h"

#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSVarNameOptionEntryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (VarNameIcon)
	{
		VarNameIcon->NodeIconClickedDelegate.AddUObject(this, &UXMSVarNameOptionEntryWidget::BroadcastOptionSelectedDelegate);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionEntryWidget Interface
 */

void UXMSVarNameOptionEntryWidget::ClearDelegates()
{
	Super::ClearDelegates();
	VarNameOptionSelectedDelegate.Clear();
}

void UXMSVarNameOptionEntryWidget::InitializeOption(int32 InOptionIndex)
{
	Super::InitializeOption(InOptionIndex);
}

void UXMSVarNameOptionEntryWidget::BroadcastOptionSelectedDelegate()
{
	VarNameOptionSelectedDelegate.Broadcast(VarName);
	Super::BroadcastOptionSelectedDelegate();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSVarNameOptionEntryWidget
 */

void UXMSVarNameOptionEntryWidget::SetVarName(const FString& InVarName)
{
	VarName = InVarName;

	VarNameIcon->SetDisplayName(VarName);
}
