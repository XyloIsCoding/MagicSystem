// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/Entry/XMSNodeClassOptionEntryWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/Base/XMSNode.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeTooltipInterface Interface
 */

void UXMSNodeClassOptionEntryWidget::InitializeTooltip(UXMSNodeTooltipWidget* TooltipWidget)
{
	Super::InitializeTooltip(TooltipWidget);

	// TODO: initialize tooltip
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionEntryWidget Interface
 */

void UXMSNodeClassOptionEntryWidget::ClearDelegates()
{
	Super::ClearDelegates();
	NodeClassOptionSelectedDelegate.Clear();
}

void UXMSNodeClassOptionEntryWidget::BroadcastOptionSelectedDelegate()
{
	NodeClassOptionSelectedDelegate.Broadcast(NodeClass);
	Super::BroadcastOptionSelectedDelegate();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeClassOptionEntryWidget
 */

void UXMSNodeClassOptionEntryWidget::SetNodeClass(TSubclassOf<UXMSNode> InNodeClass)
{
	NodeClass = InNodeClass;

	if (UTexture2D* Icon = UXMSNodeStaticLibrary::GetNodeClassIcon(NodeClass))
	{
		OptionDisplayWidget->SetDisplayIcon(Icon);
	}
	else
	{
		OptionDisplayWidget->SetDisplayIconName(UXMSNodeStaticLibrary::GetNodeClassName(NodeClass));
	}
}
