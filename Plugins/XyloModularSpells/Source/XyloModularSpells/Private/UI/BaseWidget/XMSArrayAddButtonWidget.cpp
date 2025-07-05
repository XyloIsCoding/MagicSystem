// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget/XMSArrayAddButtonWidget.h"

#include "Node/Base/XMSNodeWithArray.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


UXMSArrayAddButtonWidget::UXMSArrayAddButtonWidget()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSArrayAddButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Icon)
	{
		Icon->NodeIconClickedDelegate.AddUObject(this, &UXMSArrayAddButtonWidget::AddSubNode);
	}
}

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
