// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/XMSArraySubNodeWidget.h"
#include "Node/Base/XMSNodeWithArray.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSArraySubNodeWidget
 */

void UXMSArraySubNodeWidget::RemoveSubNode()
{
	if (UXMSNodeWithArray* ParentNode = Cast<UXMSNodeWithArray>(OwningNode.Get()))
	{
		ParentNode->RemoveSubNode(ThisNodePath.Index);
	}
}

void UXMSArraySubNodeWidget::InsertSubNode()
{
	if (UXMSNodeWithArray* ParentNode = Cast<UXMSNodeWithArray>(OwningNode.Get()))
	{
		ParentNode->InsertSubNode(ThisNodePath.Index, nullptr);
	}
}

