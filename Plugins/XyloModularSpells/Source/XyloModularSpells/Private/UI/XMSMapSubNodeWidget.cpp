// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSMapSubNodeWidget.h"
#include "Node/Base/XMSNodeWithMap.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWidget
 */

void UXMSMapSubNodeWidget::OnSpellEditorComponentSet()
{
	Super::OnSpellEditorComponentSet();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWithArrayWidget
 */

void UXMSMapSubNodeWidget::SetMapNode(UXMSNodeWithMap* OwningNode)
{
	MapNode = OwningNode;
}
