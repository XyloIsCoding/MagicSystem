// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/XMSArraySubNodeWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/Base/XMSNodeWithArray.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSSubNodeWidget
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// Events

void UXMSArraySubNodeWidget::OnSubNodeChanged(const FXMSNodePathElement& PathElement)
{
	Super::OnSubNodeChanged(PathElement);
}

// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSArraySubNodeWidget
 */

void UXMSArraySubNodeWidget::UpdateSubNodeClassIcon()
{
	if (UTexture2D* Icon = UXMSNodeStaticLibrary::GetNodeClassIconFromNode(GetSubNode()))
	{
		NodeClassIcon->SetDisplayIcon(Icon);
	}
	else
	{
		NodeClassIcon->SetDisplayName(UXMSNodeStaticLibrary::GetNodeClassNameFromNode(GetSubNode()));
	}
}

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

