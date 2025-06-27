// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeCanvasWidget.h"

#include "XMSModularSpellsSubsystem.h"
#include "Node/XMSNodeDataOverride.h"
#include "Node/Base/XMSNode.h"
#include "Node/Base/XMSNodeWithArray.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "SpellEditor/XMSSpellEditorComponent.h"
#include "UI/XMSNodeClassOptionsWidget.h"
#include "UI/SubNode/XMSSubNodeWidget.h"
#include "UI/BaseWidget/XMSWrapBox.h"
#include "UI/SubNode/XMSArraySubNodeWidget.h"
#include "UI/SubNode/XMSMapSubNodeWidget.h"
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

int32 UXMSNodeCanvasWidget::GetNodeWidgetIndex(UXMSSubNodeWidget* NodeWidget) const
{
	return NodesWrapBox->GetChildIndex(NodeWidget);
}

int32 UXMSNodeCanvasWidget::AddNodeWidgetAt(int32 Index, UXMSSubNodeWidget* NodeWidget)
{
	return  NodesWrapBox->AddChildAt(Index, NodeWidget);
}

/*--------------------------------------------------------------------------------------------------------------------*/
// Events

void UXMSNodeCanvasWidget::OnSubNodeWidgetClicked(UXMSSubNodeWidget* SubNodeWidget)
{
	SelectedSubNodeWidget = SubNodeWidget;
	if (!SubNodeWidget) return;
	
	if (UXMSNodeClassOptionsWidget* OptionsWidget = CreateOptionsWidgetForNode(SubNodeWidget))
	{
		OptionsWidget->AddToViewport();
		OptionsWidget->SetPositionInViewport(SubNodeWidget->GetCachedGeometry().GetAbsolutePosition());
	}
}

void UXMSNodeCanvasWidget::OnSubNodeClassSelected(UClass* NewClass)
{
	if (UXMSSubNodeWidget* SubNodeWidget = SelectedSubNodeWidget.Get())
	{
		if (UXMSNode* ParentNode = SubNodeWidget->GetParentNode())
		{
			ParentNode->SetSubNode(SubNodeWidget->GetPathFromParent(), NewObject<UXMSNode>(ParentNode->GetOuter(), NewClass));
		}
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

void UXMSNodeCanvasWidget::OnSubNodeWidgetUpdate(UXMSSubNodeWidget* NodeWidget, UXMSNode* NewSubNode)
{
	// Add widgets for all the sub-nodes of this sub-node
	int32 IndexInCanvas = GetNodeWidgetIndex(NodeWidget);
	if (IndexInCanvas == INDEX_NONE) return;
	
	FillNodeCanvas(++IndexInCanvas, NewSubNode);
}


void UXMSNodeCanvasWidget::FillNodeCanvas(int32& Index, UXMSNode* Node)
{
	if (!Node) return;
	
	FXMSNodeQueryResult NodeQueryResult;
	Node->GetAllSubNodes(NodeQueryResult);

	// UE_LOG(LogTemp, Warning, TEXT("AMagicSystemCharacter::AddWidgetsForSubNodes >> for [%s] -> got subnodes (%i)"), *Node->GetName(), NodeQueryResult.Nodes.Num())
	
	for (const TPair<FXMSNodePathElement, UXMSNode*>& NodeResult : NodeQueryResult.Nodes)
	{
		if (NodeResult.Value)
		{
			// UE_LOG(LogTemp, Warning, TEXT("AMagicSystemCharacter::AddWidgetsForSubNodes >> SubNode [%s], from path (%s | %i)"), *NodeResult.Value->GetName(), *NodeResult.Key.Identifier.ToString(), NodeResult.Key.Index)
			UXMSSubNodeWidget* SubNodeWidget = CreateNodeWidget(Node, NodeResult.Key);
			if (SubNodeWidget)
			{
				Index = AddNodeWidgetAt(Index, SubNodeWidget); // We are setting Index to result, since insertion Index is clamped
				++Index;
			}
			FillNodeCanvas(Index, NodeResult.Value);
		}
	}
}

UXMSSubNodeWidget* UXMSNodeCanvasWidget::CreateNodeWidget(UXMSNode* ParentNode, const FXMSNodePathElement& PathFromParentNode)
{
	if (!ParentNode) return nullptr;

	UXMSModularSpellsSubsystem* MSS = UXMSModularSpellsSubsystem::Get();
	if (!MSS) return nullptr;
	UXMSNodeDataOverride* NodesData = MSS->GetNodeDataOverride();
	if (!NodesData) return nullptr;
	FXMSNodeData* Data = NodesData->GetNodeData(ParentNode->GetClass());
	if (!Data) return nullptr;

	UXMSSubNodeWidget* Widget = nullptr;
	if (UXMSNodeWithMap* NodeWithMap = Cast<UXMSNodeWithMap>(ParentNode))
	{
		// Node with map
		bool bHasOverride = Data->WidgetClassOverride && Data->WidgetClassOverride->IsChildOf(UXMSMapSubNodeWidget::StaticClass());
		Widget = CreateWidget<UXMSMapSubNodeWidget>(GetOwningPlayer(), bHasOverride ? Data->WidgetClassOverride : NodesData->NodeWithMapWidgetClass);
	}
	else if (UXMSNodeWithArray* NodeWithArray = Cast<UXMSNodeWithArray>(ParentNode))
	{
		// Node with array
		bool bHasOverride = Data->WidgetClassOverride && Data->WidgetClassOverride->IsChildOf(UXMSArraySubNodeWidget::StaticClass());
		Widget = CreateWidget<UXMSArraySubNodeWidget>(GetOwningPlayer(), bHasOverride ? Data->WidgetClassOverride : NodesData->NodeWithArrayWidgetClass);
	}
	else if (UXMSNodeWithValue* NodeWithValue = Cast<UXMSNodeWithValue>(ParentNode))
	{
		// Node with value
		if (!Data->WidgetClassOverride) return nullptr;
		if (!Data->WidgetClassOverride->IsChildOf(UXMSNodeValueWidget::StaticClass())) return nullptr;
		Widget = CreateWidget<UXMSNodeValueWidget>(GetOwningPlayer(), Data->WidgetClassOverride);
	}
	if (!Widget) return nullptr;

	Widget->SubNodeClickedDelegate.AddUObject(this, &UXMSNodeCanvasWidget::OnSubNodeWidgetClicked);
	Widget->SubNodeChangedDelegate.AddUObject(this, &UXMSNodeCanvasWidget::OnSubNodeWidgetUpdate);
	Widget->SetOwningNode(ParentNode, PathFromParentNode);
	
	return Widget;
}

// ~Canvas Filling
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
// Class Options

UXMSNodeClassOptionsWidget* UXMSNodeCanvasWidget::CreateOptionsWidgetForNode(UXMSSubNodeWidget* NodeWidget)
{
	if (!NodeWidget) return nullptr;
	
	UXMSNodeClassOptionsWidget* OptionsWidget = ClassOptionsWidget.Get();
	if (!OptionsWidget)
	{
		UXMSModularSpellsSubsystem* MSS = UXMSModularSpellsSubsystem::Get();
		if (!MSS) return nullptr;
		UXMSNodeDataOverride* NodesData = MSS->GetNodeDataOverride();
		if (!NodesData) return nullptr;
	
		ClassOptionsWidget = OptionsWidget = CreateWidget<UXMSNodeClassOptionsWidget>(GetOwningPlayer(), NodesData->NodeOptionsWidgetClass);
		if (!OptionsWidget) return nullptr;
		
		OptionsWidget->ClassOptionChosenDelegate.AddUObject(this, &UXMSNodeCanvasWidget::OnSubNodeClassSelected);
	}

	OptionsWidget->SetVisibility(ESlateVisibility::Visible);
	
	TArray<UClass*> Options;
	NodeWidget->GetSubNodeClassOptions(Options);
	OptionsWidget->SetOptions(Options);
	
	return OptionsWidget;
}
	
// ~Class Options
/*--------------------------------------------------------------------------------------------------------------------*/


