// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeWithMapWidget.h"
#include "Node/Base/XMSNodeWithMap.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWidget
 */

void UXMSNodeWithMapWidget::OnSpellEditorComponentSet()
{
	Super::OnSpellEditorComponentSet();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWithArrayWidget
 */

void UXMSNodeWithMapWidget::SetMapNode(UXMSNodeWithMap* OwningNode)
{
	MapNode = OwningNode;
	SetNode(OwningNode);
}
