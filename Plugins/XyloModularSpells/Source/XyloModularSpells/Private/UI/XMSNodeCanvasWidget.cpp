// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeCanvasWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeCanvasWidget
 */

void UXMSNodeCanvasWidget::SetSpellEditorComponent(UXMSSpellEditorComponent* InSpellEditorComponent)
{
	SpellEditorComponent = InSpellEditorComponent;
	OnSpellEditorComponentSet();
}

void UXMSNodeCanvasWidget::OnSpellEditorComponentSet()
{
}
