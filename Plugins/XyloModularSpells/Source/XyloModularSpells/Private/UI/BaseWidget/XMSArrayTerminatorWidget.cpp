// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget/XMSArrayTerminatorWidget.h"

#include "Node/Base/XMSNodeWithArray.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


UXMSArrayTerminatorWidget::UXMSArrayTerminatorWidget()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSArrayTerminatorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Icon)
	{
		Icon->NodeIconClickedDelegate.AddUObject(this, &UXMSArrayTerminatorWidget::AddSubNode);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSArrayTerminatorWidget
 */

void UXMSArrayTerminatorWidget::AddSubNode()
{
	if (UXMSNodeWithArray* ParentNode = Cast<UXMSNodeWithArray>(OwningNode.Get()))
	{
		ParentNode->AddSubNode(nullptr);
	}
}
