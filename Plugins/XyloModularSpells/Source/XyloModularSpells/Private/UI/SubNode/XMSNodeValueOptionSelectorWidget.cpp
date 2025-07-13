// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/XMSNodeValueOptionSelectorWidget.h"

#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSNodeValueOptionSelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (SelectorDisplayWidget)
	{
		SelectorDisplayWidget->NodeIconClickedDelegate.AddUObject(this, &UXMSNodeValueOptionSelectorWidget::BroadcastOptionsRequestedDelegate);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeOptionsInterface Interface
 */

void UXMSNodeValueOptionSelectorWidget::BroadcastOptionsRequestedDelegate()
{
	OptionsRequestedDelegate.Broadcast(this);
}

void UXMSNodeValueOptionSelectorWidget::InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget)
{
	// Override in child classes to initialize option entries and bind to their delegates
}
