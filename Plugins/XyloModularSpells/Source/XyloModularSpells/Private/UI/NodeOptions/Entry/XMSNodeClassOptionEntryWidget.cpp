// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeOptions/Entry/XMSNodeClassOptionEntryWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/Base/XMSNode.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


UXMSNodeClassOptionEntryWidget::UXMSNodeClassOptionEntryWidget()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSNodeClassOptionEntryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (NodeClassIcon)
	{
		NodeClassIcon->NodeIconClickedDelegate.AddUObject(this, &UXMSNodeClassOptionEntryWidget::BroadcastOptionSelectedDelegate);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeOptionEntryWidget Interface
 */

void UXMSNodeClassOptionEntryWidget::ClearDelegates()
{
	Super::ClearDelegates();
	NodeClassOptionSelectedDelegate.Clear();
}

void UXMSNodeClassOptionEntryWidget::InitializeOption(int32 InOptionIndex)
{
	Super::InitializeOption(InOptionIndex);
}

void UXMSNodeClassOptionEntryWidget::BroadcastOptionSelectedDelegate()
{
	NodeClassOptionSelectedDelegate.Broadcast(NodeClass);
	Super::BroadcastOptionSelectedDelegate();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeClassOptionEntryWidget
 */

void UXMSNodeClassOptionEntryWidget::SetNodeClass(TSubclassOf<UXMSNode> InNodeClass)
{
	NodeClass = InNodeClass;

	if (UTexture2D* Icon = UXMSNodeStaticLibrary::GetNodeClassIcon(NodeClass))
	{
		NodeClassIcon->SetDisplayIcon(Icon);
	}
	else
	{
		NodeClassIcon->SetDisplayName(UXMSNodeStaticLibrary::GetNodeClassName(NodeClass));
	}
}
