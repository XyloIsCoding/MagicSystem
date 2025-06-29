// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget/XMSArrayAddButtonWidget.h"

#include "Node/Base/XMSNodeWithArray.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSArrayAddButtonWidget
 */

void UXMSArrayAddButtonWidget::AddSubNode()
{
	if (UXMSNodeWithArray* ParentNode = Cast<UXMSNodeWithArray>(OwningNode.Get()))
	{
		ParentNode->AddSubNode(nullptr);
	}
}
