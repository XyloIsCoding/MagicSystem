// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/XMSNodeContainerFromArrayWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/Base/XMSNodeWithArray.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeCanvasEntryWidget
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// Event

void UXMSNodeContainerFromArrayWidget::OnOwningNodeRemovedFromParent()
{
	Super::OnOwningNodeRemovedFromParent();

	if (UXMSNodeWithArray* OwningNodePtr = Cast<UXMSNodeWithArray>(OwningNode.Get()))
	{
		OwningNodePtr->SubNodeAddedDelegate.Remove(OnOwningNodeSubNodeAddedHandle);
		OwningNodePtr->SubNodeRemovedDelegate.Remove(OnOwningNodeSubNodeRemovedHandle);
	}
}

// ~Event
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// OwningNode

void UXMSNodeContainerFromArrayWidget::OnOwningNodeSet()
{
	Super::OnOwningNodeSet();

	if (UXMSNodeWithArray* OwningNodePtr = Cast<UXMSNodeWithArray>(OwningNode.Get()))
	{
		OnOwningNodeSubNodeAddedHandle = OwningNodePtr->SubNodeAddedDelegate.AddUObject(this, &ThisClass::OnOwningNodeSubNodeAdded);
		OnOwningNodeSubNodeRemovedHandle = OwningNodePtr->SubNodeRemovedDelegate.AddUObject(this, &ThisClass::OnOwningNodeSubNodeRemoved);
	}
}

// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeContainerFromArrayWidget
 */

void UXMSNodeContainerFromArrayWidget::RemoveSubNode()
{
	if (UXMSNodeWithArray* ParentNode = Cast<UXMSNodeWithArray>(OwningNode.Get()))
	{
		ParentNode->RemoveSubNode(ThisNodePath.Index);
	}
}

void UXMSNodeContainerFromArrayWidget::InsertSubNode()
{
	if (UXMSNodeWithArray* ParentNode = Cast<UXMSNodeWithArray>(OwningNode.Get()))
	{
		ParentNode->InsertSubNode(ThisNodePath.Index, nullptr);
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/
// Events

void UXMSNodeContainerFromArrayWidget::OnOwningNodeSubNodeAdded(const FXMSNodePathElement& PathElement)
{
	// If a node got added before this one, then we want to shift up the index to account for that
	// Look at TXMSMultiNodeContainer::ShiftUpPathIndexes
	// We do not have to worry about risking increasing the index of the added NodeContainerWidget because
	// that widget is created in OnSubNodeContainerAdded (still bound to SubNodeContainerAddedDelegate)
	if (ThisNodePath.Index >= PathElement.Index)
	{
		ThisNodePath.Index += 1;
	}
}

void UXMSNodeContainerFromArrayWidget::OnOwningNodeSubNodeRemoved(const FXMSNodePathElement& PathElement)
{
	// If a node got removed before this one, then we want to shift down the index to account for that
	// Look at TXMSMultiNodeContainer::ShiftDownPathIndexes
	if (ThisNodePath.Index > PathElement.Index)
	{
		ThisNodePath.Index -= 1;
	}
	else if (ThisNodePath.Index == PathElement.Index)
	{
		OnOwningNodeRemovedFromParent();
	}
}

// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/


