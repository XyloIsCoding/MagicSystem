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

void UXMSNodeWidget::SetNode(UXMSNode* OwningNode)
{
	Node = OwningNode;
	if (OwningNode)
	{
		OwningNode->RemovedFromParentDelegate.AddUObject(this, &ThisClass::OnNodeRemovedFromParent);
	}
	OnNodeSet();
}

void UXMSNodeWidget::OnNodeSet()
{
}

void UXMSNodeWidget::OnNodeRemovedFromParent()
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
