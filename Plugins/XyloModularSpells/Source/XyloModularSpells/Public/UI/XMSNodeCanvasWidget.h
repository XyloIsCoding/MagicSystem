// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeClassOptionsWidget.h"
#include "XMSNodeEditorWidget.h"
#include "XMSTypes.h"
#include "XMSNodeCanvasWidget.generated.h"

class UXMSNodeWithValue;
class UXMSNodeValueWidget;
class UXMSArrayAddButtonWidget;
class UXMSNodeWithArray;
class UXMSNodeCanvasEntryWidget;
class UXMSNode;
class UXMSWrapBox;
class UXMSNodeContainerWidget;
class UXMSSpellEditorComponent;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeCanvasWidget : public UXMSNodeEditorWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeEditorWidget Interface
	 */

protected:
	virtual void OnSpellEditorComponentSet() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeCanvasWidget
	 */

public:
	int32 GetNodeWidgetIndex(UXMSNodeCanvasEntryWidget* NodeWidget) const;
protected:
	int32 AddNodeWidgetAt(int32 Index, UXMSNodeCanvasEntryWidget* NodeWidget);
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UXMSWrapBox> NodesWrapBox;

/*--------------------------------------------------------------------------------------------------------------------*/
	// Events

protected:
	/** Bound to all SubNode Widgets */
	virtual void OnNodeContainerWidgetClicked(UXMSNodeContainerWidget* SubNodeWidget);
	/** Bound to ClassOptionsWidget */
	virtual void OnNodeClassSelected(UClass* NewClass);
	/** Bound to all SubNode Widgets */
	virtual void OnNodeContainerWidgetUpdate(UXMSNodeContainerWidget* NodeWidget, UXMSNode* NewNode);
	/** Bound to all SubNode Widgets */
	virtual void OnNodeContainerWidgetSubNodeAdded(UXMSNodeContainerWidget* NodeWidget, UXMSNode* AddedSubNodeParent, const FXMSNodePathElement& AddedSubNodePathFromParent);

	// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// Canvas Filling
	
public:
	void InitializeNodeCanvas(UXMSNode* Node);
protected:
	/** Fill node canvas for a specific node
	 * @param NodeWidget: NodeContainerWidget representing the NodeContainer holding Node
	 * @param Index: Where to insert the NodeContainerWidgets for Node and its children
	 * @param Node: The node to fill the canvas with */
	void FillNodeCanvas(UXMSNodeContainerWidget* NodeWidget, int32& Index, UXMSNode* Node);
	void FillNodeCanvasSingleChild(UXMSNodeContainerWidget* NodeWidget, int32& Index, UXMSNode* Node, const FXMSNodePathElement& PathForSubNode);
	void AddArrayTerminationWidget(UXMSNodeContainerWidget* NodeWidget, int32& Index, UXMSNodeWithArray* Node);
	void AddValueSelectorWidget(UXMSNodeContainerWidget* NodeWidget, int32& Index, UXMSNodeWithValue* Node);
	UXMSNodeContainerWidget* CreateNodeWidget(UXMSNode* ParentNode, const FXMSNodePathElement& PathFromParentNode);
	UXMSArrayAddButtonWidget* CreateArrayTerminationWidget(UXMSNodeWithArray* ArrayNode);
	UXMSNodeValueWidget* CreateValueSelectorWidget(UXMSNodeWithValue* ValueNode);
	
	// ~Canvas Filling
/*--------------------------------------------------------------------------------------------------------------------*/
	
/*--------------------------------------------------------------------------------------------------------------------*/
	// Class Options

public:
	virtual UXMSNodeClassOptionsWidget* GetOrCreateOptionsWidgetForNode(UXMSNodeContainerWidget* NodeWidget);
protected:
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeClassOptionsWidget> ClassOptionsWidget;
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeContainerWidget> SelectedSubNodeWidget;
	
	// ~Class Options
/*--------------------------------------------------------------------------------------------------------------------*/


};
