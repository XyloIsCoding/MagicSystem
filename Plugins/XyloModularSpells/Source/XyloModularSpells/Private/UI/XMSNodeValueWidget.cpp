// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeValueWidget.h"
#include "Node/Base/XMSNodeWithValue.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSSubNodeWidget
 */

void UXMSNodeValueWidget::OnSpellEditorComponentSet()
{
	Super::OnSpellEditorComponentSet();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeValueWidget
 */

void UXMSNodeValueWidget::SetValueNode(UXMSNodeWithValue* OwningNode)
{
	ValueNode = OwningNode;
}
