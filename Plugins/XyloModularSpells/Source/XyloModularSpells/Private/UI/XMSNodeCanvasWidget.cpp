// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeCanvasWidget.h"

#include "XMSModularSpellsSubsystem.h"
#include "XMSNodeStaticLibrary.h"
#include "XyloModularSpells.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Node/XMSNodeData.h"
#include "Node/XMSNodeDataRegistry.h"
#include "Node/Base/XMSNode.h"
#include "Node/Base/XMSNodeWithArray.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "UI/NodeOptions/XMSNodeOptionsSelectionWidget.h"
#include "UI/BaseWidget/XMSArrayTerminatorWidget.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"
#include "UI/SubNode/XMSNodeContainerWidget.h"
#include "UI/BaseWidget/XMSWrapBox.h"
#include "UI/NodeOptions/XMSNodeOptionsInterface.h"
#include "UI/SubNode/XMSNodeContainerFromArrayWidget.h"
#include "UI/SubNode/XMSNodeContainerFromMapWidget.h"
#include "UI/SubNode/XMSNodeValueSelectorWidget.h"


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
	return NodesWrapBox->AddChildAt(Index, NodeWidget);
}

/*--------------------------------------------------------------------------------------------------------------------*/
// Events

void UXMSNodeCanvasWidget::OnOptionsRequested(UWidget* OptionsRequestingWidget)
{
	if (!OptionsRequestingWidget) return;
	IXMSNodeOptionsInterface* NodeOptionsInterface = Cast<IXMSNodeOptionsInterface>(OptionsRequestingWidget);
	if (!NodeOptionsInterface) return;

	if (UXMSNodeOptionsSelectionWidget* OptionsWidget = GetOrCreateOptionsWidgetForNode(NodeOptionsInterface))
	{
		if (!OptionsWidget->IsInViewport())
		{
			OptionsWidget->AddToViewport();
		}
		else
		{
			OptionsWidget->SetFocus();
		}
		OptionsWidget->SetVisibility(ESlateVisibility::Visible);
		OptionsWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
		FVector2D PixelPos;
		FVector2D ViewportPos;
		USlateBlueprintLibrary::LocalToViewport(this, OptionsRequestingWidget->GetCachedGeometry(), OptionsRequestingWidget->GetCachedGeometry().Size / 2, PixelPos, ViewportPos);
		OptionsWidget->SetPositionInViewport(PixelPos);
	}
}

void UXMSNodeCanvasWidget::OnNodeOptionSelected(int32 Index)
{
}

void UXMSNodeCanvasWidget::OnNodeContainerWidgetUpdate(UXMSNodeContainerWidget* NodeWidget, UXMSNode* NewNode)
{
	// Only fill canvas for this node if not nullptr
	if (!NewNode) return;
	
	// Add widgets for all the sub-nodes of this sub-node
	int32 IndexInCanvas = GetNodeWidgetIndex(NodeWidget);
	if (IndexInCanvas == INDEX_NONE) return;
	
	FillNodeCanvas(NodeWidget, ++IndexInCanvas, NewNode);
	NodesWrapBox->Rebuild();
}

void UXMSNodeCanvasWidget::OnNodeContainerWidgetSubNodeAdded(UXMSNodeContainerWidget* NodeWidget, UXMSNode* AddedSubNodeParent, const FXMSNodePathElement& AddedSubNodePathFromParent)
{
	if (!NodeWidget) return;
	if (!NodeWidget->SubNodeContainerWidgets.IsValidIndex(AddedSubNodePathFromParent.Index)) return;
	
	// We add new container widget before the one at the needed index
	int32 IndexInCanvas = GetNodeWidgetIndex(NodeWidget->SubNodeContainerWidgets[AddedSubNodePathFromParent.Index].Get());
	if (IndexInCanvas == INDEX_NONE) return;
	
	// Fill canvas for this specific node container of parent node
	FillNodeCanvasSingleChild(NodeWidget, IndexInCanvas, AddedSubNodeParent, AddedSubNodePathFromParent);
	NodesWrapBox->Rebuild();
}

// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// Canvas Filling

void UXMSNodeCanvasWidget::InitializeNodeCanvas(UXMSNode* Node)
{
	NodesWrapBox->ClearChildren();
	int32 Index = 0;
	FillNodeCanvas(nullptr, Index, Node);
}

void UXMSNodeCanvasWidget::FillNodeCanvas(UXMSNodeContainerWidget* NodeWidget, int32& Index, UXMSNode* Node)
{
	if (!Node) return;
	
	FXMSNodeQueryResult SubNodeContainers;
	Node->GetAllSubNodes(SubNodeContainers);

	for (const TPair<FXMSNodePathElement, UXMSNode*>& SubNodeContainer : SubNodeContainers.Nodes)
	{
		FillNodeCanvasSingleChild(NodeWidget, Index, Node, SubNodeContainer.Key);
	}
	
	if (UXMSNodeWithArray* NodeWithArray = Cast<UXMSNodeWithArray>(Node))
	{
		AddArrayTerminationWidget(NodeWidget, Index, NodeWithArray);
	}
	else if (UXMSNodeWithValue* NodeWithValue = Cast<UXMSNodeWithValue>(Node))
	{
		AddValueSelectorWidget(NodeWidget, Index, NodeWithValue);
	}
}

void UXMSNodeCanvasWidget::FillNodeCanvasSingleChild(UXMSNodeContainerWidget* NodeWidget, int32& Index, UXMSNode* Node, const FXMSNodePathElement& PathForSubNode)
{
	if (!Node) return;
	
	UXMSNodeContainerWidget* SubNodeWidget = CreateNodeWidget(Node, PathForSubNode);
	if (SubNodeWidget)
	{
		if (NodeWidget && Node->IsA<UXMSNodeWithArray>())
		{
			NodeWidget->SubNodeContainerWidgets.Insert(SubNodeWidget, FMath::Clamp(PathForSubNode.Index, 0, NodeWidget->SubNodeContainerWidgets.Num()));
		}
		Index = AddNodeWidgetAt(Index, SubNodeWidget); // We are setting Index to result, since insertion Index is clamped
		++Index;
	}

	// Recursive fill if sub-node is set
	if (UXMSNode* SubNode = Node->GetSubNode(PathForSubNode))
	{
		FillNodeCanvas(SubNodeWidget, Index, SubNode);
	}
}

void UXMSNodeCanvasWidget::AddArrayTerminationWidget(UXMSNodeContainerWidget* NodeWidget, int32& Index, UXMSNodeWithArray* Node)
{
	if (!Node) return;
	
	UXMSArrayTerminatorWidget* ArrayTerminator = CreateArrayTerminationWidget(Node);
	if (ArrayTerminator)
	{
		if (NodeWidget) NodeWidget->SubNodeContainerWidgets.Add(ArrayTerminator);
		Index = AddNodeWidgetAt(Index, ArrayTerminator);
		++Index;
	}
}

void UXMSNodeCanvasWidget::AddValueSelectorWidget(UXMSNodeContainerWidget* NodeWidget, int32& Index, UXMSNodeWithValue* Node)
{
	if (!Node) return;
	
	UXMSNodeValueSelectorWidget* ValueSelector = CreateValueSelectorWidget(Node);
	if (ValueSelector)
	{
		Index = AddNodeWidgetAt(Index, ValueSelector);
		++Index;
	}
}

UXMSNodeContainerWidget* UXMSNodeCanvasWidget::CreateNodeWidget(UXMSNode* ParentNode, const FXMSNodePathElement& PathFromParentNode)
{
	if (!ParentNode) return nullptr;
	
	UXMSNodeDataRegistry* NodeDataRegistry = UXMSNodeStaticLibrary::GetNodeClassDataRegistry();
	if (!NodeDataRegistry) return nullptr;

	// Node with sub-nodes
	UXMSNodeContainerWidget* Widget = nullptr;
	if (UXMSNodeWithMap* NodeWithMap = Cast<UXMSNodeWithMap>(ParentNode))
	{
		// Node with map
		Widget = CreateWidget<UXMSNodeContainerFromMapWidget>(GetOwningPlayer(), NodeDataRegistry->NodeWithMapWidgetClass);
	}
	else if (UXMSNodeWithArray* NodeWithArray = Cast<UXMSNodeWithArray>(ParentNode))
	{
		// Node with array
		Widget = CreateWidget<UXMSNodeContainerFromArrayWidget>(GetOwningPlayer(), NodeDataRegistry->NodeWithArrayWidgetClass);
	}
	if (!Widget) return nullptr;

	if (IXMSNodeOptionsInterface* NodeOptionsInterface = Cast<IXMSNodeOptionsInterface>(Widget))
	{
		NodeOptionsInterface->GetOptionsRequestedDelegate().AddUObject(this, &UXMSNodeCanvasWidget::OnOptionsRequested);
	}
	Widget->NodeChangedDelegate.AddUObject(this, &UXMSNodeCanvasWidget::OnNodeContainerWidgetUpdate);
	Widget->SubNodeContainerAddedDelegate.AddUObject(this, &UXMSNodeCanvasWidget::OnNodeContainerWidgetSubNodeAdded);
	Widget->SetOwningNodeAndPath(ParentNode, PathFromParentNode);
	
	return Widget;
}

UXMSArrayTerminatorWidget* UXMSNodeCanvasWidget::CreateArrayTerminationWidget(UXMSNodeWithArray* ArrayNode)
{
	if (!ArrayNode) return nullptr;
	UXMSNodeDataRegistry* NodeDataRegistry = UXMSNodeStaticLibrary::GetNodeClassDataRegistry();
	if (!NodeDataRegistry) return nullptr;
		
	UXMSArrayTerminatorWidget* SubNodeWidget = CreateWidget<UXMSArrayTerminatorWidget>(GetOwningPlayer(), NodeDataRegistry->ArrayTerminatorWidgetClass);
	if (SubNodeWidget)
	{
		SubNodeWidget->SetOwningNode(ArrayNode);
	}
	return SubNodeWidget;
}

UXMSNodeValueSelectorWidget* UXMSNodeCanvasWidget::CreateValueSelectorWidget(UXMSNodeWithValue* ValueNode)
{
	if (!ValueNode) return nullptr;
	UXMSNodeData* Data = UXMSNodeStaticLibrary::GetNodeClassData(ValueNode->GetClass());
	if (!Data) return nullptr;

	if (!Data->ValueSelectorWidgetClass)
	{
		UE_LOG(LogXyloModularSpells, Error, TEXT("UXMSNodeCanvasWidget::CreateValueSelectorWidget >> ValueSelectorWidgetClass non specified for [%s]"), *ValueNode->GetClass()->GetName())
		return nullptr;
	}
	
	UXMSNodeValueSelectorWidget* NodeValueWidget = CreateWidget<UXMSNodeValueSelectorWidget>(GetOwningPlayer(), Data->ValueSelectorWidgetClass);
	if (!NodeValueWidget) return nullptr;
	
	if (IXMSNodeOptionsInterface* NodeOptionsInterface = Cast<IXMSNodeOptionsInterface>(NodeValueWidget))
	{
		NodeOptionsInterface->GetOptionsRequestedDelegate().AddUObject(this, &UXMSNodeCanvasWidget::OnOptionsRequested);
	}
	NodeValueWidget->SetOwningNode(ValueNode);
	
	return NodeValueWidget;
}

// ~Canvas Filling
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// Class Options

UXMSNodeOptionsSelectionWidget* UXMSNodeCanvasWidget::GetOrCreateOptionsWidgetForNode(IXMSNodeOptionsInterface* NodeOptionsInterface)
{
	if (!NodeOptionsInterface) return nullptr;
	
	UXMSNodeOptionsSelectionWidget* OptionsWidget = ClassOptionsWidget.Get();
	if (!OptionsWidget)
	{
		UXMSModularSpellsSubsystem* MSS = UXMSModularSpellsSubsystem::Get();
		if (!MSS) return nullptr;
		UXMSNodeDataRegistry* NodesData = MSS->GetNodeDataRegistry();
		if (!NodesData) return nullptr;
	
		ClassOptionsWidget = OptionsWidget = CreateWidget<UXMSNodeOptionsSelectionWidget>(GetOwningPlayer(), NodesData->NodeOptionsWidgetClass);
		if (!OptionsWidget) return nullptr;
		
		OptionsWidget->OptionSelectedDelegate.AddUObject(this, &UXMSNodeCanvasWidget::OnNodeOptionSelected);
	}

	NodeOptionsInterface->InitializeOptions(OptionsWidget);
	return OptionsWidget;
}
	
// ~Class Options
/*--------------------------------------------------------------------------------------------------------------------*/


