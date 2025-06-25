// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSArraySubNodeWidget.h"
#include "Node/Base/XMSNodeWithArray.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWidget
 */

void UXMSArraySubNodeWidget::OnSpellEditorComponentSet()
{
	Super::OnSpellEditorComponentSet();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSArraySubNodeWidget
 */

void UXMSArraySubNodeWidget::SetArrayNode(UXMSNodeWithArray* OwningNode)
{
	ArrayNode = OwningNode;
}
