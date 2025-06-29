// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/XMSNodeContainerFromMapWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/XMSNodeDataRegistry.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeContainerFromMapWidget
 */

void UXMSNodeContainerFromMapWidget::UpdateSubNodeTypeIcon()
{
	if (UTexture2D* Icon = GetSubNodeTypeIcon())
	{
		NodeTypeIcon->SetVisibility(ESlateVisibility::Visible);
		NodeTypeIcon->SetDisplayIcon(Icon);
	}
	else
	{
		NodeTypeIcon->SetVisibility(ESlateVisibility::Collapsed);
	}
}

bool UXMSNodeContainerFromMapWidget::GetSubNodeTypeDisplayData(UTexture2D*& OutGlyph, FText& OutDisplayName, FText& OutDescription) const
{
	UXMSNode* ParentNode = OwningNode.Get();
	if (!ParentNode) return false;
	
	FXMSNodeData* ParentNodeData = UXMSNodeStaticLibrary::GetNodeClassData(ParentNode->GetClass());
	if (!ParentNodeData) return false;

	FXMSSubNodeData* SubNodeData = ParentNodeData->GetSubNodeData(ThisNodePath.Identifier);
	if (!SubNodeData) return false;

	OutGlyph = SubNodeData->Glyph;
	OutDisplayName = SubNodeData->Name;
	OutDescription = SubNodeData->Description;
	return true;
}

UTexture2D* UXMSNodeContainerFromMapWidget::GetSubNodeTypeIcon() const
{
	UXMSNode* ParentNode = OwningNode.Get();
	if (!ParentNode) return nullptr;
	
	FXMSNodeData* ParentNodeData = UXMSNodeStaticLibrary::GetNodeClassData(ParentNode->GetClass());
	if (!ParentNodeData) return nullptr;

	FXMSSubNodeData* SubNodeData = ParentNodeData->GetSubNodeData(ThisNodePath.Identifier);
	if (!SubNodeData) return nullptr;

	return SubNodeData->Glyph;
}

