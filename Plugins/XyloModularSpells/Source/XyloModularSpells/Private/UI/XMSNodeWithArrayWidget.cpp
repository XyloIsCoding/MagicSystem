// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeWithArrayWidget.h"
#include "Node/Base/XMSNodeWithArray.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWidget
 */

void UXMSNodeWithArrayWidget::OnSpellEditorComponentSet()
{
	Super::OnSpellEditorComponentSet();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWithArrayWidget
 */

void UXMSNodeWithArrayWidget::SetArrayNode(UXMSNodeWithArray* OwningNode)
{
	ArrayNode = OwningNode;
	SetNode(OwningNode);
}
