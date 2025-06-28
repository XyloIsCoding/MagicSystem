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

void UXMSSubNodeWidget::ChangeSubNodeClass(UClass* NewClass)
{
	if (UXMSNode* ParentNode = OwningNode.Get())
	{
		ParentNode->SetSubNode(ThisNodePath, NewObject<UXMSNode>(ParentNode->GetOuter(), NewClass));
	}
}

void UXMSSubNodeWidget::ResetSubNodeIcon()
{
}

void UXMSSubNodeWidget::UpdateSubNodeIcon(UXMSNode* SubNode)
{
	
}

/*--------------------------------------------------------------------------------------------------------------------*/
// Events

void UXMSSubNodeWidget::BroadcastSubNodeClicked()
{
	SubNodeClickedDelegate.Broadcast(this);
}

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
		BP_ResetSubNodeIcon();
		return;
	}
	UpdateSubNodeIcon(NewSubNode);
	BP_UpdateSubNodeIcon(NewSubNode);
	
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

UXMSNode* UXMSSubNodeWidget::GetParentNode() const
{
	return OwningNode.Get();
}

const FXMSNodePathElement& UXMSSubNodeWidget::GetPathFromParent() const
{
	return ThisNodePath;
}

void UXMSSubNodeWidget::OnOwningNodeSet()
{
}

// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/

