// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSSubNodeWidget.h"

#include "Node/Base/XMSNode.h"


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
	if (UXMSNode* OwningNodePtr = OwningNode.Get())
	{
		UXMSNode* ThisNode = OwningNodePtr->GetSubNode(ThisNodePath);
		if (ThisNode) return ThisNode->GetName();
	}
	return FString(TEXT("[-]"));
}

void UXMSSubNodeWidget::SetOwningNode(UXMSNode* InOwningNode, const FXMSNodePathElement& PathFromOwningNode)
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

void UXMSSubNodeWidget::OnOwningNodeSet()
{
}

void UXMSSubNodeWidget::OnOwningNodeRemovedFromParent()
{
	// Remove widget from the widget container
	RemoveFromParent();
}

void UXMSSubNodeWidget::SetSpellEditorComponent(UXMSSpellEditorComponent* InSpellEditorComponent)
{
	SpellEditorComponent = InSpellEditorComponent;
	OnSpellEditorComponentSet();
}

void UXMSSubNodeWidget::OnSpellEditorComponentSet()
{
}
