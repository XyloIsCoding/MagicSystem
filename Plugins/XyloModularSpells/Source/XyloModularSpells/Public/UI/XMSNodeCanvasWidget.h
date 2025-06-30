// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeClassOptionsWidget.h"
#include "XMSNodeEditorWidget.h"
#include "XMSTypes.h"
#include "XMSNodeCanvasWidget.generated.h"

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
	virtual void OnNodeContainerWidgetUpdate(UXMSNodeContainerWidget* NodeWidget, UXMSNode* NewSubNode);
	/** Bound to all SubNode Widgets */
	virtual void OnNodeContainerWidgetSubNodeAdded(UXMSNodeContainerWidget* NodeWidget, UXMSNode* AddedSubNodeParent, const FXMSNodePathElement& AddedSubNodePathFromParent);

	// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// Canvas Filling
	
public:
	void InitializeNodeCanvas(UXMSNode* Node);
protected:
	void FillNodeCanvas(int32& Index, UXMSNode* Node);
	void AddArrayTerminationWidget(int32& Index, UXMSNode* Node);
	UXMSNodeCanvasEntryWidget* CreateNodeWidget(UXMSNode* ParentNode, const FXMSNodePathElement& PathFromParentNode);
	UXMSArrayAddButtonWidget* CreateArrayTerminationWidget(UXMSNodeWithArray* ParentNode);
	
	// ~Canvas Filling
/*--------------------------------------------------------------------------------------------------------------------*/
	
/*--------------------------------------------------------------------------------------------------------------------*/
	// Class Options

public:
	virtual UXMSNodeClassOptionsWidget* CreateOptionsWidgetForNode(UXMSNodeContainerWidget* NodeWidget);
protected:
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeClassOptionsWidget> ClassOptionsWidget;
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeContainerWidget> SelectedSubNodeWidget;
	
	// ~Class Options
/*--------------------------------------------------------------------------------------------------------------------*/


};
