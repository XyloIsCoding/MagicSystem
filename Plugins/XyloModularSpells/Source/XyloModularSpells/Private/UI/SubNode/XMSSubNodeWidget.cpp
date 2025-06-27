// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/XMSSubNodeWidget.h"

#include "Node/Base/XMSNode.h"
#include "SpellEditor/XMSSpellEditorComponent.h"
#include "UI/XMSNodeCanvasWidget.h"


UXMSSubNodeWidget::UXMSSubNodeWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget
 */

FReply UXMSSubNodeWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	SubNodeClickedDelegate.Broadcast(this, InGeometry, InMouseEvent, GetSubNode());
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSSubNodeWidget
 */

FString UXMSSubNodeWidget::GetCurrentNodeSelectionName() const
{
	if (UXMSNode* ThisNode = GetSubNode())
	{
		return ThisNode->GetName();
	}
	return FString(TEXT("[-]"));
}

UXMSNode* UXMSSubNodeWidget::GetSubNode() const
{
	UXMSNode* OwningNodePtr = OwningNode.Get();
	if (!OwningNodePtr) return nullptr;

	return OwningNodePtr->GetSubNode(ThisNodePath);
}

void UXMSSubNodeWidget::GetSubNodeClassOptions(TArray<UClass*>& OutClassOptions)
{
	if (UXMSNode* OwningNodePtr = OwningNode.Get())
	{
		OwningNodePtr->GetSubNodeClassOptions(ThisNodePath, OutClassOptions);
	}
}

void UXMSSubNodeWidget::ResetSubNodeIcon()
{
}

void UXMSSubNodeWidget::UpdateSubNodeIcon(UXMSNode& SubNode)
{
	
}

/*--------------------------------------------------------------------------------------------------------------------*/
// Events

void UXMSSubNodeWidget::OnOwningNodeRemovedFromParent()
{
	// Remove widget from the widget container
	RemoveFromParent();
}

void UXMSSubNodeWidget::OnSubNodeChanged(const FXMSNodePathElement& PathElement)
{
	if (PathElement != ThisNodePath) return;

	UXMSNode* NewSubNode = GetSubNode();
	if (!NewSubNode)
	{
		ResetSubNodeIcon();
		return;
	}
	UpdateSubNodeIcon(*NewSubNode);

	// Broadcast change (in particular to inform canvas that it should redraw the sub-nodes chain)
	SubNodeChangedDelegate.Broadcast(this, NewSubNode);
}

// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// OwningNode

void UXMSSubNodeWidget::SetOwningNode(UXMSNode* InOwningNode, const FXMSNodePathElement& PathFromOwningNode)
{
	OwningNode = InOwningNode;
	ThisNodePath = PathFromOwningNode;
	if (InOwningNode)
	{
		InOwningNode->RemovedFromParentDelegate.AddUObject(this, &ThisClass::OnOwningNodeRemovedFromParent);
		InOwningNode->SubNodeChangedDelegate.AddUObject(this, &ThisClass::OnSubNodeChanged);
	}
	OnOwningNodeSet();
	BP_OnOwningNodeSet();
}

void UXMSSubNodeWidget::OnOwningNodeSet()
{
}

// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/

