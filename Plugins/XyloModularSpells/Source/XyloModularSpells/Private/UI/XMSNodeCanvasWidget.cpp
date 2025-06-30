// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeCanvasWidget.h"

#include "XMSModularSpellsSubsystem.h"
#include "XMSNodeStaticLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Node/XMSNodeDataRegistry.h"
#include "Node/Base/XMSNode.h"
#include "Node/Base/XMSNodeWithArray.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "UI/XMSNodeClassOptionsWidget.h"
#include "UI/BaseWidget/XMSArrayAddButtonWidget.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"
#include "UI/SubNode/XMSNodeContainerWidget.h"
#include "UI/BaseWidget/XMSWrapBox.h"
#include "UI/SubNode/XMSNodeContainerFromArrayWidget.h"
#include "UI/SubNode/XMSNodeContainerFromMapWidget.h"
#include "UI/SubNode/XMSNodeValueWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeEditorWidget Interface
 */

void UXMSNodeCanvasWidget::OnSpellEditorComponentSet()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeCanvasWidget
 */

int32 UXMSNodeCanvasWidget::GetNodeWidgetIndex(UXMSNodeCanvasEntryWidget* NodeWidget) const
{
	return NodesWrapBox->GetChildIndex(NodeWidget);
}

int32 UXMSNodeCanvasWidget::AddNodeWidgetAt(int32 Index, UXMSNodeCanvasEntryWidget* NodeWidget)
{
	return  NodesWrapBox->AddChildAt(Index, NodeWidget);
}

/*--------------------------------------------------------------------------------------------------------------------*/
// Events

void UXMSNodeCanvasWidget::OnNodeContainerWidgetClicked(UXMSNodeContainerWidget* SubNodeWidget)
{
	SelectedSubNodeWidget = SubNodeWidget;
	if (!SubNodeWidget) return;
	
	if (UXMSNodeClassOptionsWidget* OptionsWidget = CreateOptionsWidgetForNode(SubNodeWidget))
	{
		OptionsWidget->AddToViewport();
		OptionsWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
		FVector2D PixelPos;
		FVector2D ViewportPos;
		USlateBlueprintLibrary::LocalToViewport(this, SubNodeWidget->GetCachedGeometry(), FVector2D(0.5f, 0.5f), PixelPos, ViewportPos);
		OptionsWidget->SetPositionInViewport(ViewportPos);
	}
}

void UXMSNodeCanvasWidget::OnNodeClassSelected(UClass* NewClass)
{
	if (UXMSNodeContainerWidget* SubNodeWidget = SelectedSubNodeWidget.Get())
	{
		SubNodeWidget->ChangeNodeClass(NewClass);
	}
}

void UXMSNodeCanvasWidget::OnNodeContainerWidgetUpdate(UXMSNodeContainerWidget* NodeWidget, UXMSNode* NewSubNode)
{
	// Only fill canvas for this node if not nullptr
	if (!NewSubNode) return;
	
	// Add widgets for all the sub-nodes of this sub-node
	int32 IndexInCanvas = GetNodeWidgetIndex(NodeWidget);
	if (IndexInCanvas == INDEX_NONE) return;
	
	FillNodeCanvas(++IndexInCanvas, NewSubNode);
}

void UXMSNodeCanvasWidget::OnNodeContainerWidgetSubNodeAdded(UXMSNodeContainerWidget* NodeWidget, UXMSNode* AddedSubNodeParent, const FXMSNodePathElement& AddedSubNodePathFromParent)
{
	// TODO: instead of using NodeWidget, we use the array of NodeContainers ptr it owns, and use AddedSubNodePathFromParent.Index to select the right one
	int32 IndexInCanvas = GetNodeWidgetIndex(NodeWidget);

	// Fill canvas for this specific node container of parent node
	// (is the same as calling FillNodeCanvas but only for one sub-node container instead of all of them)
	UXMSNodeCanvasEntryWidget* SubNodeWidget = CreateNodeWidget(AddedSubNodeParent, AddedSubNodePathFromParent);
	if (SubNodeWidget)
	{
		IndexInCanvas = AddNodeWidgetAt(IndexInCanvas, SubNodeWidget); // We are setting Index to result, since insertion Index is clamped
		++IndexInCanvas;
	}

	// Recursive fill if sub-node is set
	if (UXMSNode* AddedSubNode = AddedSubNodeParent->GetSubNode(AddedSubNodePathFromParent))
	{
		FillNodeCanvas(IndexInCanvas, AddedSubNode);
	}
}

// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// Canvas Filling

void UXMSNodeCanvasWidget::InitializeNodeCanvas(UXMSNode* Node)
{
	NodesWrapBox->ClearChildren();
	int32 Index = 0;
	FillNodeCanvas(Index, Node);
}

void UXMSNodeCanvasWidget::FillNodeCanvas(int32& Index, UXMSNode* Node)
{
	if (!Node) return;
	
	FXMSNodeQueryResult SubNodeContainers;
	Node->GetAllSubNodes(SubNodeContainers);

	for (const TPair<FXMSNodePathElement, UXMSNode*>& NodeContainer : SubNodeContainers.Nodes)
	{
		UXMSNodeCanvasEntryWidget* SubNodeWidget = CreateNodeWidget(Node, NodeContainer.Key);
		if (SubNodeWidget)
		{
			Index = AddNodeWidgetAt(Index, SubNodeWidget); // We are setting Index to result, since insertion Index is clamped
			++Index;
		}

		// Recursive fill if sub-node is set
		if (NodeContainer.Value)
		{
			FillNodeCanvas(Index, NodeContainer.Value);
		}
	}

	// TODO: find out why the order is not right
	AddArrayTerminationWidget(Index, Node);
}

void UXMSNodeCanvasWidget::AddArrayTerminationWidget(int32& Index, UXMSNode* Node)
{
	if (UXMSNodeWithArray* NewSubNodeWithArray = Cast<UXMSNodeWithArray>(Node))
	{
		UXMSArrayAddButtonWidget* ArrayTerminator = CreateArrayTerminationWidget(NewSubNodeWithArray);
		if (ArrayTerminator)
		{
			AddNodeWidgetAt(Index, ArrayTerminator);
			++Index; // TODO: chekc if this fixed the + icon ordering issue
		}
	}
}

UXMSNodeCanvasEntryWidget* UXMSNodeCanvasWidget::CreateNodeWidget(UXMSNode* ParentNode, const FXMSNodePathElement& PathFromParentNode)
{
	if (!ParentNode) return nullptr;
	
	UXMSNodeDataRegistry* NodeDataRegistry = UXMSNodeStaticLibrary::GetNodeClassDataRegistry();
	if (!NodeDataRegistry) return nullptr;
	FXMSNodeData* Data = NodeDataRegistry->GetNodeData(ParentNode->GetClass());

	// Node with value
	if (UXMSNodeWithValue* NodeWithValue = Cast<UXMSNodeWithValue>(ParentNode))
	{
		// Node with value
		if (!Data || !Data->WidgetClassOverride) return nullptr;
		if (!Data->WidgetClassOverride->IsChildOf(UXMSNodeValueWidget::StaticClass())) return nullptr;
		UXMSNodeValueWidget* Widget = CreateWidget<UXMSNodeValueWidget>(GetOwningPlayer(), Data->WidgetClassOverride);
		if (Widget)
		{
			Widget->SetOwningNode(ParentNode);
		}
		return Widget;
	}

	// Node with sub-nodes
	UXMSNodeContainerWidget* Widget = nullptr;
	if (UXMSNodeWithMap* NodeWithMap = Cast<UXMSNodeWithMap>(ParentNode))
	{
		// Node with map
		bool bHasOverride = Data && Data->WidgetClassOverride && Data->WidgetClassOverride->IsChildOf(UXMSNodeContainerFromMapWidget::StaticClass());
		Widget = CreateWidget<UXMSNodeContainerFromMapWidget>(GetOwningPlayer(), bHasOverride ? Data->WidgetClassOverride : NodeDataRegistry->NodeWithMapWidgetClass);
	}
	else if (UXMSNodeWithArray* NodeWithArray = Cast<UXMSNodeWithArray>(ParentNode))
	{
		// Node with array
		bool bHasOverride = Data && Data->WidgetClassOverride && Data->WidgetClassOverride->IsChildOf(UXMSNodeContainerFromArrayWidget::StaticClass());
		Widget = CreateWidget<UXMSNodeContainerFromArrayWidget>(GetOwningPlayer(), bHasOverride ? Data->WidgetClassOverride : NodeDataRegistry->NodeWithArrayWidgetClass);
	}
	if (!Widget) return nullptr;

	Widget->NodeClickedDelegate.AddUObject(this, &UXMSNodeCanvasWidget::OnNodeContainerWidgetClicked);
	Widget->NodeChangedDelegate.AddUObject(this, &UXMSNodeCanvasWidget::OnNodeContainerWidgetUpdate);
	Widget->SubNodeAddedDelegate.AddUObject(this, &UXMSNodeCanvasWidget::OnNodeContainerWidgetSubNodeAdded);
	Widget->SetOwningNodeAndPath(ParentNode, PathFromParentNode);
	
	return Widget;
}

UXMSArrayAddButtonWidget* UXMSNodeCanvasWidget::CreateArrayTerminationWidget(UXMSNodeWithArray* ParentNode)
{
	if (!ParentNode) return nullptr;
	UXMSNodeDataRegistry* NodeDataRegistry = UXMSNodeStaticLibrary::GetNodeClassDataRegistry();
	if (!NodeDataRegistry) return nullptr;
		
	UXMSArrayAddButtonWidget* SubNodeWidget = CreateWidget<UXMSArrayAddButtonWidget>(GetOwningPlayer(), NodeDataRegistry->ArrayAddWidgetClass);
	if (SubNodeWidget)
	{
		SubNodeWidget->SetOwningNode(ParentNode);
		if (NodeDataRegistry->ArrayAddTexture)
		{
			SubNodeWidget->Icon->SetDisplayIcon(NodeDataRegistry->ArrayAddTexture);
		}
	}
	return SubNodeWidget;
}

// ~Canvas Filling
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// Class Options

UXMSNodeClassOptionsWidget* UXMSNodeCanvasWidget::CreateOptionsWidgetForNode(UXMSNodeContainerWidget* NodeWidget)
{
	if (!NodeWidget) return nullptr;
	
	UXMSNodeClassOptionsWidget* OptionsWidget = ClassOptionsWidget.Get();
	if (!OptionsWidget)
	{
		UXMSModularSpellsSubsystem* MSS = UXMSModularSpellsSubsystem::Get();
		if (!MSS) return nullptr;
		UXMSNodeDataRegistry* NodesData = MSS->GetNodeDataRegistry();
		if (!NodesData) return nullptr;
	
		ClassOptionsWidget = OptionsWidget = CreateWidget<UXMSNodeClassOptionsWidget>(GetOwningPlayer(), NodesData->NodeOptionsWidgetClass);
		if (!OptionsWidget) return nullptr;
		
		OptionsWidget->ClassOptionChosenDelegate.AddUObject(this, &UXMSNodeCanvasWidget::OnNodeClassSelected);
	}

	OptionsWidget->SetVisibility(ESlateVisibility::Visible);
	
	TArray<UClass*> Options;
	NodeWidget->GetNodeClassOptions(Options);
	OptionsWidget->SetOptions(Options);
	
	return OptionsWidget;
}
	
// ~Class Options
/*--------------------------------------------------------------------------------------------------------------------*/


