// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/XMSNodeContainerWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/XMSNodeDataRegistry.h"
#include "Node/Base/XMSNode.h"
#include "Node/Base/XMSNodeWithArray.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"


UXMSNodeContainerWidget::UXMSNodeContainerWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeContainerWidget
 */

void UXMSNodeContainerWidget::UpdateNodeClassIcon()
{
	if (UTexture2D* Icon = UXMSNodeStaticLibrary::GetNodeClassIconFromNode(GetNode()))
	{
		NodeClassIcon->SetDisplayIcon(Icon);
	}
	else
	{
		NodeClassIcon->SetDisplayName(UXMSNodeStaticLibrary::GetNodeClassNameFromNode(GetNode()));
	}
}

FString UXMSNodeContainerWidget::GetNodeName() const
{
	if (UXMSNode* ThisNode = GetNode())
	{
		return ThisNode->GetName();
	}
	return FString(TEXT("[-]"));
}

bool UXMSNodeContainerWidget::GetNodeDisplayData(UTexture2D*& OutGlyph, FText& OutDisplayName, FText& OutDescription) const
{
	UXMSNode* ThisNode = GetNode();
	if (!ThisNode) return false;
	
	FXMSNodeData* NodeData = UXMSNodeStaticLibrary::GetNodeClassData(ThisNode->GetClass());
	if (!NodeData) return false;

	OutGlyph = NodeData->Glyph;
	OutDisplayName = NodeData->Name;
	OutDescription = NodeData->Description;
	return true;
}

UXMSNode* UXMSNodeContainerWidget::GetNode() const
{
	UXMSNode* OwningNodePtr = OwningNode.Get();
	if (!OwningNodePtr) return nullptr;

	return OwningNodePtr->GetSubNode(ThisNodePath);
}

void UXMSNodeContainerWidget::GetNodeClassOptions(TArray<UClass*>& OutClassOptions)
{
	if (UXMSNode* OwningNodePtr = OwningNode.Get())
	{
		OwningNodePtr->GetSubNodeClassOptions(ThisNodePath, OutClassOptions);
	}
}

void UXMSNodeContainerWidget::ChangeNodeClass(UClass* NewClass)
{
	if (UXMSNode* ParentNode = OwningNode.Get())
	{
		ParentNode->SetSubNode(ThisNodePath, NewObject<UXMSNode>(ParentNode->GetOuter(), NewClass));
	}
}

void UXMSNodeContainerWidget::ResetNodeIcon()
{
}

void UXMSNodeContainerWidget::UpdateNodeIcon(UXMSNode* Node)
{
	
}

/*--------------------------------------------------------------------------------------------------------------------*/
// Events

void UXMSNodeContainerWidget::BroadcastNodeClicked()
{
	NodeClickedDelegate.Broadcast(this);
}

void UXMSNodeContainerWidget::OnNodeChanged()
{
	UXMSNode* NewNode = GetNode();
	if (!NewNode)
	{
		ResetNodeIcon();
		BP_NodeIcon();
	}
	else
	{
		UpdateNodeIcon(NewNode);
		BP_UpdateNodeIcon(NewNode);

		if (UXMSNodeWithArray* NodeWithArray = Cast<UXMSNodeWithArray>(NewNode))
		{
			NodeWithArray->SubNodeAddedDelegate.AddUObject(this, &ThisClass::OnSubNodeAdded);
		}	
	}
	
	// Broadcast change (in particular to inform canvas that it should redraw the sub-nodes chain)
	NodeChangedDelegate.Broadcast(this, NewNode);
}

void UXMSNodeContainerWidget::OnSubNodeAdded(const FXMSNodePathElement& PathElement)
{
	UXMSNode* OwningNodePtr = OwningNode.Get();
	if (!OwningNodePtr) return;
	
	UXMSNode* AddedSubNode = OwningNodePtr->GetSubNode(PathElement);
	
	// Broadcast addition (in particular to inform canvas that it should redraw the sub-nodes chain)
	SubNodeAddedDelegate.Broadcast(this, AddedSubNode, PathElement);
}

void UXMSNodeContainerWidget::OnOwningNodeSubNodeChanged(const FXMSNodePathElement& PathElement)
{
	if (PathElement != ThisNodePath) return;
	OnNodeChanged();
}

void UXMSNodeContainerWidget::OnOwningNodeSubNodeAdded(const FXMSNodePathElement& PathElement)
{
	// If a node got added before this one, then we want to shift up the index to account for that
	// Look at TXMSMultiNodeContainer::ShiftUpPathIndexes
	// We do not have to worry about risking increasing the index of the added NodeContainerWidget because
	// that widget is created in OnSubNodeAdded (still bound to SubNodeAddedDelegate)
	if (ThisNodePath.Index > PathElement.Index)
	{
		ThisNodePath.Index += 1;
	}
}

void UXMSNodeContainerWidget::OnOwningNodeSubNodeRemoved(const FXMSNodePathElement& PathElement)
{
	// If a node got removed before this one, then we want to shift down the index to account for that
	// Look at TXMSMultiNodeContainer::ShiftDownPathIndexes
	if (ThisNodePath.Index > PathElement.Index)
	{
		ThisNodePath.Index -= 1;
	}
}

// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// OwningNode

void UXMSNodeContainerWidget::SetOwningNodeAndPath(UXMSNode* InOwningNode, const FXMSNodePathElement& PathFromOwningNode)
{
	ThisNodePath = PathFromOwningNode;
	if (InOwningNode)
	{
		InOwningNode->SubNodeChangedDelegate.AddUObject(this, &ThisClass::OnOwningNodeSubNodeChanged);
		if (UXMSNodeWithArray* OwningNodeWithArray = Cast<UXMSNodeWithArray>(InOwningNode))
		{
			OwningNodeWithArray->SubNodeAddedDelegate.AddUObject(this, &UXMSNodeContainerWidget::OnOwningNodeSubNodeAdded);
			OwningNodeWithArray->SubNodeRemovedDelegate.AddUObject(this, &UXMSNodeContainerWidget::OnOwningNodeSubNodeRemoved);
		}
	}
	SetOwningNode(InOwningNode);
}

// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/

