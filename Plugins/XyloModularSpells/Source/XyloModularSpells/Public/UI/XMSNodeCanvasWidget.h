// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

/*--------------------------------------------------------------------------------------------------------------------*/
	// Canvas Filling
	
public:
	void InitializeNodeCanvas(UXMSNode* Node);
protected:
	void OnSubNodeWidgetUpdate(UXMSSubNodeWidget* NodeWidget, UXMSNode* NewSubNode);
	void FillNodeCanvas(int32& Index, UXMSNode* Node);
	UXMSSubNodeWidget* CreateNodeWidget(UXMSNode* ParentNode, const FXMSNodePathElement& PathFromParentNode);
	
	// ~Canvas Filling
/*--------------------------------------------------------------------------------------------------------------------*/

protected:
	void OnSubNodeWidgetClicked(UXMSSubNodeWidget* NodeWidget, const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UXMSNode* NewSubNode);
	
public:
	int32 GetNodeWidgetIndex(UXMSSubNodeWidget* NodeWidget) const;
protected:
	int32 AddNodeWidgetAt(int32 Index, UXMSSubNodeWidget* NodeWidget);
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UXMSWrapBox> NodesWrapBox;
};
