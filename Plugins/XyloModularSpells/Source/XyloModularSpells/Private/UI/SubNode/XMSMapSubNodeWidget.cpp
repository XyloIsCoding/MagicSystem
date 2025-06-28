// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/XMSMapSubNodeWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/XMSNodeDataOverride.h"
#include "Node/Base/XMSNodeWithMap.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSMapSubNodeWidget
 */

bool UXMSMapSubNodeWidget::GetSubNodeTypeDisplayData(UTexture2D*& OutGlyph, FText& OutDisplayName, FText& OutDescription) const
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

