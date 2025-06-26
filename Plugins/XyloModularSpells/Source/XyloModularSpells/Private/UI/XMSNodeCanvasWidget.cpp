// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeCanvasWidget.h"

#include "UI/XMSSubNodeWidget.h"
#include "UI/BaseWidget/XMSWrapBox.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeCanvasWidget
 */

int32 UXMSNodeCanvasWidget::GetNodeWidgetIndex(UXMSSubNodeWidget* NodeWidget)
{
	return NodesWrapBox->GetChildIndex(NodeWidget);
}

int32 UXMSNodeCanvasWidget::AddNodeWidgetAt(int32 Index, UXMSSubNodeWidget* NodeWidget)
{
	return NodesWrapBox->AddChildAt(Index, NodeWidget);
}

void UXMSNodeCanvasWidget::SetSpellEditorComponent(UXMSSpellEditorComponent* InSpellEditorComponent)
{
	SpellEditorComponent = InSpellEditorComponent;
	OnSpellEditorComponentSet();
}

void UXMSNodeCanvasWidget::OnSpellEditorComponentSet()
{
}
