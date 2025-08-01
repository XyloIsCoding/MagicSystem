// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget/XMSNodeCanvasEntryWidget.h"

#include "Node/Base/XMSNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeTooltipInterface Interface
 */

void UXMSNodeCanvasEntryWidget::BroadcastTooltipRequestedDelegate()
{
	TooltipRequestedDelegate.Broadcast(this);
}

void UXMSNodeCanvasEntryWidget::InitializeTooltip(UXMSNodeTooltipWidget* TooltipWidget)
{
	// Implement in child classes to initialize the tooltip with information about this entry
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeCanvasEntryWidget
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// Events

void UXMSNodeCanvasEntryWidget::OnOwningNodeRemovedFromParent()
{
	// Remove widget from the widget container
	RemoveFromParent();

	if (UXMSNode* OwningNodePtr = OwningNode.Get())
	{
		OwningNodePtr->RemovedFromParentDelegate.Remove(OnOwningNodeRemovedFromParentHandle);
	}
}

// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// OwningNode

void UXMSNodeCanvasEntryWidget::SetOwningNode(UXMSNode* InOwningNode)
{
	OwningNode = InOwningNode;
	if (InOwningNode)
	{
		OnOwningNodeRemovedFromParentHandle = InOwningNode->RemovedFromParentDelegate.AddUObject(this, &ThisClass::OnOwningNodeRemovedFromParent);
	}
	OnOwningNodeSet();
	BP_OnOwningNodeSet();
}

void UXMSNodeCanvasEntryWidget::OnOwningNodeSet()
{
}

// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/

