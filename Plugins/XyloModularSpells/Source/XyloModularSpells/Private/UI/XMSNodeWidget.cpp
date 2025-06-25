// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeWidget.h"

#include "Node/Base/XMSNode.h"


UXMSNodeWidget::UXMSNodeWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWidget
 */

FString UXMSNodeWidget::GetCurrentNodeSelectionName() const
{
	if (UXMSNode* OwningNodePtr = OwningNode.Get())
	{
		UXMSNode* ThisNode = OwningNodePtr->GetSubNode(ThisNodePath);
		if (ThisNode) return ThisNode->GetName();
	}
	return FString(TEXT("[-]"));
}

void UXMSNodeWidget::SetOwningNode(UXMSNode* InOwningNode, const FXMSNodePathElement& PathFromOwningNode)
{
	OwningNode = InOwningNode;
	ThisNodePath = PathFromOwningNode;
	if (InOwningNode)
	{
		InOwningNode->RemovedFromParentDelegate.AddUObject(this, &ThisClass::OnOwningNodeRemovedFromParent);
	}
	OnOwningNodeSet();
	BP_OnOwningNodeSet();
}

void UXMSNodeWidget::OnOwningNodeSet()
{
}

void UXMSNodeWidget::OnOwningNodeRemovedFromParent()
{
	// Remove widget from the widget container
	RemoveFromParent();
}

void UXMSNodeWidget::SetSpellEditorComponent(UXMSSpellEditorComponent* InSpellEditorComponent)
{
	SpellEditorComponent = InSpellEditorComponent;
	OnSpellEditorComponentSet();
}

void UXMSNodeWidget::OnSpellEditorComponentSet()
{
}
