// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/XMSSubNodeWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/XMSNodeDataRegistry.h"
#include "Node/Base/XMSNode.h"


UXMSSubNodeWidget::UXMSSubNodeWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSSubNodeWidget
 */

FString UXMSSubNodeWidget::GetCurrentNodeSelectionName() const
{
	if (UXMSNode* ThisNode = GetSubNode())
	{
		return ThisNode->GetName();
	}
	return FString(TEXT("[-]"));
}

bool UXMSSubNodeWidget::GetSubNodeDisplayData(UTexture2D*& OutGlyph, FText& OutDisplayName, FText& OutDescription) const
{
	UXMSNode* ThisNode = GetSubNode();
	if (!ThisNode) return false;
	
	FXMSNodeData* NodeData = UXMSNodeStaticLibrary::GetNodeClassData(ThisNode->GetClass());
	if (!NodeData) return false;

	OutGlyph = NodeData->Glyph;
	OutDisplayName = NodeData->Name;
	OutDescription = NodeData->Description;
	return true;
}

UXMSNode* UXMSSubNodeWidget::GetSubNode() const
{
	UXMSNode* OwningNodePtr = OwningNode.Get();
	if (!OwningNodePtr) return nullptr;

	return OwningNodePtr->GetSubNode(ThisNodePath);
}

void UXMSSubNodeWidget::GetSubNodeClassOptions(TArray<UClass*>& OutClassOptions)
{
	if (UXMSNode* OwningNodePtr = OwningNode.Get())
	{
		OwningNodePtr->GetSubNodeClassOptions(ThisNodePath, OutClassOptions);
	}
}

void UXMSSubNodeWidget::ChangeSubNodeClass(UClass* NewClass)
{
	if (UXMSNode* ParentNode = OwningNode.Get())
	{
		ParentNode->SetSubNode(ThisNodePath, NewObject<UXMSNode>(ParentNode->GetOuter(), NewClass));
		// TODO: if it is array node, listen to new element added and redraw
	}
}

void UXMSSubNodeWidget::ResetSubNodeIcon()
{
}

void UXMSSubNodeWidget::UpdateSubNodeIcon(UXMSNode* SubNode)
{
	
}

/*--------------------------------------------------------------------------------------------------------------------*/
// Events

void UXMSSubNodeWidget::BroadcastSubNodeClicked()
{
	SubNodeClickedDelegate.Broadcast(this);
}

void UXMSSubNodeWidget::OnSubNodeChanged(const FXMSNodePathElement& PathElement)
{
	if (PathElement != ThisNodePath) return;

	UXMSNode* NewSubNode = GetSubNode();
	if (!NewSubNode)
	{
		ResetSubNodeIcon();
		BP_ResetSubNodeIcon();
		return;
	}
	UpdateSubNodeIcon(NewSubNode);
	BP_UpdateSubNodeIcon(NewSubNode);
	
	// Broadcast change (in particular to inform canvas that it should redraw the sub-nodes chain)
	SubNodeChangedDelegate.Broadcast(this, NewSubNode);
}

// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// OwningNode

void UXMSSubNodeWidget::SetOwningNodeAndPath(UXMSNode* InOwningNode, const FXMSNodePathElement& PathFromOwningNode)
{
	ThisNodePath = PathFromOwningNode;
	if (InOwningNode)
	{
		InOwningNode->SubNodeChangedDelegate.AddUObject(this, &ThisClass::OnSubNodeChanged);
	}
	SetOwningNode(InOwningNode);
}

// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/

