// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeWithValueWidget.h"
#include "Node/Base/XMSNodeWithValue.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWidget
 */

void UXMSNodeWithValueWidget::OnSpellEditorComponentSet()
{
	Super::OnSpellEditorComponentSet();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWithValueWidget
 */

void UXMSNodeWithValueWidget::SetValueNode(UXMSNodeWithValue* OwningNode)
{
	ValueNode = OwningNode;
	SetNode(OwningNode);
}
