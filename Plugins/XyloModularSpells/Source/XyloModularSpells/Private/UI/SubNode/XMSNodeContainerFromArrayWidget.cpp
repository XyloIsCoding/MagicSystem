// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/XMSNodeContainerFromArrayWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/Base/XMSNodeWithArray.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeContainerFromArrayWidget
 */

void UXMSNodeContainerFromArrayWidget::RemoveSubNode()
{
	if (UXMSNodeWithArray* ParentNode = Cast<UXMSNodeWithArray>(OwningNode.Get()))
	{
		ParentNode->RemoveSubNode(ThisNodePath.Index);
	}
}

void UXMSNodeContainerFromArrayWidget::InsertSubNode()
{
	if (UXMSNodeWithArray* ParentNode = Cast<UXMSNodeWithArray>(OwningNode.Get()))
	{
		ParentNode->InsertSubNode(ThisNodePath.Index, nullptr);
	}
}

