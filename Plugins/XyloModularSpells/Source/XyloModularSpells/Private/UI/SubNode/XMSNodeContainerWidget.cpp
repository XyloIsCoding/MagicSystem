// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/XMSNodeContainerWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/XMSNodeData.h"
#include "Node/XMSNodeDataRegistry.h"
#include "Node/Base/XMSNode.h"
#include "Node/Base/XMSNodeWithArray.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"
#include "UI/NodeOptions/Entry/XMSNodeClassOptionEntryWidget.h"
#include "UI/NodeOptions/XMSNodeOptionsSelectionWidget.h"


UXMSNodeContainerWidget::UXMSNodeContainerWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSNodeContainerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (NodeClassIcon)
	{
		NodeClassIcon->NodeIconClickedDelegate.AddUObject(this, &UXMSNodeContainerWidget::BroadcastNodeClicked);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeCanvasEntryWidget Interface
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// Event
	
void UXMSNodeContainerWidget::OnOwningNodeRemovedFromParent()
{
	Super::OnOwningNodeRemovedFromParent();

	if (UXMSNode* OwningNodePtr = OwningNode.Get())
	{
		OwningNodePtr->SubNodeChangedDelegate.Remove(OnOwningNodeSubNodeChangedHandle);
	}
}

// ~Event
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// OwningNode

void UXMSNodeContainerWidget::OnOwningNodeSet()
{
	Super::OnOwningNodeSet();

	if (UXMSNode* OwningNodePtr = OwningNode.Get())
	{
		OnOwningNodeSubNodeChangedHandle = OwningNodePtr->SubNodeChangedDelegate.AddUObject(this, &ThisClass::OnOwningNodeSubNodeChanged);
	}
}

// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeOptionsInterface Interface
 */

void UXMSNodeContainerWidget::InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget)
{
	UXMSNodeDataRegistry* NodeDataRegistry = UXMSNodeStaticLibrary::GetNodeClassDataRegistry();
	if (!NodeDataRegistry) return;
	
	TArray<TSubclassOf<UXMSNode>> Options;
	GetNodeClassOptions(Options);
	
	TArray<UXMSNodeClassOptionEntryWidget*> OptionWidgets;
	OptionsSelectionWidget->InitializeOptions<UXMSNodeClassOptionEntryWidget>(Options.Num(), NodeDataRegistry->NodeClassOptionWidgetClass, OptionWidgets, true);

	for (auto It = OptionWidgets.CreateIterator(); It; ++It)
	{
		if (!Options.IsValidIndex(It.GetIndex()))
		{
			UE_LOG(LogXyloModularSpells, Warning, TEXT("UXMSNodeContainerWidget::InitializeOptions >> No matching class option for option widget??"))
			break;
		}
		if (UXMSNodeClassOptionEntryWidget* OptionWidget = *It)
		{
			OptionWidget->SetNodeClass(Options[It.GetIndex()]);
			OptionWidget->NodeClassOptionSelectedDelegate.AddUObject(this, &ThisClass::ChangeNodeClass);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeContainerWidget
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// Icon

void UXMSNodeContainerWidget::UpdateNodeClassIcon()
{
	if (UTexture2D* Icon = UXMSNodeStaticLibrary::GetNodeClassIconFromNode(GetNode()))
	{
		NodeClassIcon->SetDisplayIcon(Icon);
	}
	else
	{
		NodeClassIcon->SetDisplayIconName(UXMSNodeStaticLibrary::GetNodeClassNameFromNode(GetNode()));
	}
}

bool UXMSNodeContainerWidget::GetNodeDisplayData(UTexture2D*& OutGlyph, FText& OutDisplayName, FText& OutDescription) const
{
	UXMSNode* ThisNode = GetNode();
	if (!ThisNode) return false;
	
	UXMSNodeData* NodeData = UXMSNodeStaticLibrary::GetNodeClassData(ThisNode->GetClass());
	if (!NodeData) return false;

	OutGlyph = NodeData->Glyph;
	OutDisplayName = NodeData->Name;
	OutDescription = NodeData->Description;
	return true;
}

void UXMSNodeContainerWidget::ResetNodeIcon()
{
}

void UXMSNodeContainerWidget::UpdateNodeIcon(UXMSNode* Node)
{
}

// ~Icon
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// ContainedNode

FString UXMSNodeContainerWidget::GetNodeName() const
{
	if (UXMSNode* ThisNode = GetNode())
	{
		return ThisNode->GetName();
	}
	return FString(TEXT("[-]"));
}

UXMSNode* UXMSNodeContainerWidget::GetNode() const
{
	UXMSNode* OwningNodePtr = OwningNode.Get();
	if (!OwningNodePtr) return nullptr;

	return OwningNodePtr->GetSubNode(ThisNodePath);
}

void UXMSNodeContainerWidget::GetNodeClassOptions(TArray<TSubclassOf<UXMSNode>>& OutClassOptions)
{
	if (UXMSNode* OwningNodePtr = OwningNode.Get())
	{
		OwningNodePtr->GetSubNodeClassOptions(ThisNodePath, OutClassOptions);
	}
}

void UXMSNodeContainerWidget::ChangeNodeClass(TSubclassOf<UXMSNode> NewClass)
{
	UXMSNode* ParentNode = OwningNode.Get();
	if (!ParentNode) return;
	
	ParentNode->SetSubNode(ThisNodePath, NewObject<UXMSNode>(ParentNode->GetOuter(), NewClass));
}

// ~ContainedNode
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// Events

void UXMSNodeContainerWidget::BroadcastNodeClicked()
{
	OptionsRequestedDelegate.Broadcast(this);
}

void UXMSNodeContainerWidget::OnNodeChanged()
{
	SubNodeContainerWidgets.Empty();
	UXMSNode* NewNode = GetNode();
	if (!NewNode)
	{
		ResetNodeIcon();
		BP_ResetNodeIcon();

		SetVisibility(ESlateVisibility::Visible);
		return;
	}
	
	UpdateNodeIcon(NewNode);
	BP_UpdateNodeIcon(NewNode);

	if (UXMSNodeWithArray* NodeWithArray = Cast<UXMSNodeWithArray>(NewNode))
	{
		NodeWithArray->SubNodeAddedDelegate.AddUObject(this, &ThisClass::OnSubNodeContainerAdded);
		NodeWithArray->SubNodeRemovedDelegate.AddUObject(this, &ThisClass::OnSubNodeContainerRemoved);
	}

	if (UXMSNodeData* NodeData = UXMSNodeStaticLibrary::GetNodeClassData(NewNode->GetClass()))
	{
		// Hide this widget if requested
		if (NodeData->bHideInSpellEditor)
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UXMSNodeContainerWidget::OnSubNodeContainerAdded(const FXMSNodePathElement& PathElement)
{
	UXMSNode* NewNode = GetNode();
	if (!NewNode) return;
	
	// Broadcast addition (in particular to inform canvas that it should redraw the sub-nodes chain)
	SubNodeContainerAddedDelegate.Broadcast(this, NewNode, PathElement);
}

void UXMSNodeContainerWidget::OnSubNodeContainerRemoved(const FXMSNodePathElement& PathElement)
{
	if (!SubNodeContainerWidgets.IsValidIndex(PathElement.Index)) return;
	SubNodeContainerWidgets.RemoveAt(PathElement.Index);
}

void UXMSNodeContainerWidget::OnOwningNodeSubNodeChanged(const FXMSNodePathElement& PathElement)
{
	if (PathElement != ThisNodePath) return;

	OnNodeChanged();
	// Broadcast change (in particular to inform canvas that it should redraw the sub-nodes chain)
	NodeChangedDelegate.Broadcast(this, GetNode());
}

// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// OwningNode

void UXMSNodeContainerWidget::SetOwningNodeAndPath(UXMSNode* InOwningNode, const FXMSNodePathElement& PathFromOwningNode)
{
	ThisNodePath = PathFromOwningNode;
	SetOwningNode(InOwningNode);
	OnNodeChanged();
}

// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/

