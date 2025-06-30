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
 * UXMSNodeCanvasEntryWidget
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// OwningNode

void UXMSNodeContainerWidget::OnOwningNodeSet()
{
	Super::OnOwningNodeSet();

	if (UXMSNode* OwningNodePtr = OwningNode.Get())
	{
		OwningNodePtr->SubNodeChangedDelegate.AddUObject(this, &ThisClass::OnOwningNodeSubNodeChanged);
	}
}

// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/

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
		BP_ResetNodeIcon();
	}
	else
	{
		UpdateNodeIcon(NewNode);
		BP_UpdateNodeIcon(NewNode);

		if (UXMSNodeWithArray* NodeWithArray = Cast<UXMSNodeWithArray>(NewNode))
		{
			NodeWithArray->SubNodeAddedDelegate.AddUObject(this, &ThisClass::OnSubNodeContainerAdded);
		}	
	}
	
	// Broadcast change (in particular to inform canvas that it should redraw the sub-nodes chain)
	NodeChangedDelegate.Broadcast(this, NewNode);
}

void UXMSNodeContainerWidget::OnSubNodeContainerAdded(const FXMSNodePathElement& PathElement)
{
	UXMSNode* OwningNodePtr = OwningNode.Get();
	if (!OwningNodePtr) return;
	
	// Broadcast addition (in particular to inform canvas that it should redraw the sub-nodes chain)
	SubNodeContainerAddedDelegate.Broadcast(this, OwningNodePtr, PathElement);
}

void UXMSNodeContainerWidget::OnOwningNodeSubNodeChanged(const FXMSNodePathElement& PathElement)
{
	if (PathElement != ThisNodePath) return;
	OnNodeChanged();
}

// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// OwningNode

void UXMSNodeContainerWidget::SetOwningNodeAndPath(UXMSNode* InOwningNode, const FXMSNodePathElement& PathFromOwningNode)
{
	ThisNodePath = PathFromOwningNode;
	SetOwningNode(InOwningNode);
}

// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/

