// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NodeOptions/XMSNodeOptionsSelectionWidget.h"
#include "XMSNodeEditorWidget.h"
#include "XMSTypes.h"
#include "XMSNodeCanvasWidget.generated.h"

class IXMSNodeOptionsInterface;
class UXMSNodeWithValue;
class UXMSNodeValueSelectorWidget;
class UXMSArrayTerminatorWidget;
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
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeTooltipWidget> TooltipWidget;

/*--------------------------------------------------------------------------------------------------------------------*/
	// Events

protected:
	/** Bound to all SubNode Widgets */
	virtual void OnOptionsRequested(UWidget* OptionsRequestingWidget);
	/** Bound to OptionsSelectionWidget in GetOrCreateOptionsWidgetForNode */
	virtual void OnOptionsSelectionCompleted(bool bSuccess);
	/** Bound to all SubNode Widgets */
	virtual void OnNodeContainerWidgetUpdate(UXMSNodeContainerWidget* NodeWidget, UXMSNode* NewNode);
	/** Bound to all SubNode Widgets */
	virtual void OnNodeContainerWidgetSubNodeAdded(UXMSNodeContainerWidget* NodeWidget, UXMSNode* AddedSubNodeParent, const FXMSNodePathElement& AddedSubNodePathFromParent);
	/** Bound to all Canvas Entries */
	virtual void TooltipRequested(UWidget* Widget);
	
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
	UXMSNodeCanvasEntryWidget* CreateCanvasEntryWidget(TSubclassOf<UXMSNodeCanvasEntryWidget> WidgetClass);
	UXMSNodeContainerWidget* CreateNodeWidget(UXMSNode* ParentNode, const FXMSNodePathElement& PathFromParentNode);
	UXMSArrayTerminatorWidget* CreateArrayTerminationWidget(UXMSNodeWithArray* ArrayNode);
	UXMSNodeValueSelectorWidget* CreateValueSelectorWidget(UXMSNodeWithValue* ValueNode);
	
	// ~Canvas Filling
/*--------------------------------------------------------------------------------------------------------------------*/
	
/*--------------------------------------------------------------------------------------------------------------------*/
	// Class Options

public:
	virtual UXMSNodeOptionsSelectionWidget* GetOrCreateOptionsWidgetForNode(IXMSNodeOptionsInterface* NodeOptionsInterface);
protected:
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeOptionsSelectionWidget> OptionsSelectionWidget;
	
	// ~Class Options
/*--------------------------------------------------------------------------------------------------------------------*/
};
