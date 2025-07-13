// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/Entry/XMSNodeClassOptionEntryWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Components/RichTextBlock.h"
#include "Node/XMSNodeData.h"
#include "Node/Base/XMSNode.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"
#include "UI/NodeTooltip/XMSNodeTooltipWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeTooltipInterface Interface
 */

void UXMSNodeClassOptionEntryWidget::InitializeTooltip(UXMSNodeTooltipWidget* TooltipWidget)
{
	Super::InitializeTooltip(TooltipWidget);

	if (!TooltipWidget) return;

	// Container tooltip
	if (UXMSNodeData* OwningNodeData = UXMSNodeStaticLibrary::GetNodeClassData(NodeClass))
	{
		TooltipWidget->Title->SetText(OwningNodeData->Name);
		TooltipWidget->Body->SetText(OwningNodeData->Description);
	}
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
