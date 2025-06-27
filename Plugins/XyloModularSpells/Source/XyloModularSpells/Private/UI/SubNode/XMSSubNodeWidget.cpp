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
 * UXMSNodeEditorWidget Interface
 */

void UXMSSubNodeWidget::OnSpellEditorComponentSet()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSSubNodeWidget
 */

FString UXMSSubNodeWidget::GetCurrentNodeSelectionName() const
{
	if (UXMSNode* OwningNodePtr = OwningNode.Get())
	{
		UXMSNode* ThisNode = OwningNodePtr->GetSubNode(ThisNodePath);
		if (ThisNode) return ThisNode->GetName();
	}
	return FString(TEXT("[-]"));
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

	UXMSNode* OwningNodePtr = OwningNode.Get();
	if (!OwningNodePtr) return;

	UXMSNode* NewSubNode = OwningNodePtr->GetSubNode(PathElement);
	if (!NewSubNode)
	{
		ResetSubNodeIcon();
		return;
	}
	UpdateSubNodeIcon(*NewSubNode);
	
	UXMSSpellEditorComponent* SpellEditor = SpellEditorComponent.Get();
	if (!SpellEditor) return;

	UXMSNodeCanvasWidget* Canvas = SpellEditor->GetOrCreateNodeCanvas(GetOwningPlayer());
	if (!Canvas) return;

	// Add widgets for all the sub-nodes of this sub-node
	int32 IndexInCanvas = Canvas->GetNodeWidgetIndex(this);
	SpellEditor->FillNodeCanvas(GetOwningPlayer(), Canvas, ++IndexInCanvas, NewSubNode);
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

