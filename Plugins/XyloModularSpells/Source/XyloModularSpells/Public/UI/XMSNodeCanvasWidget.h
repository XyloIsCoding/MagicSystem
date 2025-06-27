// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeClassOptionsWidget.h"
#include "XMSNodeEditorWidget.h"
#include "XMSTypes.h"
#include "XMSNodeCanvasWidget.generated.h"

class UXMSNode;
class UXMSWrapBox;
class UXMSSubNodeWidget;
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
	int32 GetNodeWidgetIndex(UXMSSubNodeWidget* NodeWidget) const;
protected:
	int32 AddNodeWidgetAt(int32 Index, UXMSSubNodeWidget* NodeWidget);
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UXMSWrapBox> NodesWrapBox;

/*--------------------------------------------------------------------------------------------------------------------*/
	// Events

protected:
	/** Bound to all SubNode Widgets */
	virtual void OnSubNodeWidgetClicked(UXMSSubNodeWidget* SubNodeWidget);
	/** Bound to ClassOptionsWidget */
	virtual void OnSubNodeClassSelected(UClass* NewClass);

	// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// Canvas Filling
	
public:
	void InitializeNodeCanvas(UXMSNode* Node);
protected:
	virtual void OnSubNodeWidgetUpdate(UXMSSubNodeWidget* NodeWidget, UXMSNode* NewSubNode);
	void FillNodeCanvas(int32& Index, UXMSNode* Node);
	UXMSSubNodeWidget* CreateNodeWidget(UXMSNode* ParentNode, const FXMSNodePathElement& PathFromParentNode);
	
	// ~Canvas Filling
/*--------------------------------------------------------------------------------------------------------------------*/
	
/*--------------------------------------------------------------------------------------------------------------------*/
	// Class Options

public:
	virtual UXMSNodeClassOptionsWidget* CreateOptionsWidgetForNode(UXMSSubNodeWidget* NodeWidget);
protected:
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeClassOptionsWidget> ClassOptionsWidget;
	UPROPERTY()
	TWeakObjectPtr<UXMSSubNodeWidget> SelectedSubNodeWidget;
	
	// ~Class Options
/*--------------------------------------------------------------------------------------------------------------------*/


};
