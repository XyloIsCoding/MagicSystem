// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeEditorWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeEditorWidget
 */

void UXMSNodeEditorWidget::SetSpellEditorComponent(UXMSSpellEditorComponent* InSpellEditorComponent)
{
	SpellEditorComponent = InSpellEditorComponent;
	OnSpellEditorComponentSet();
}

void UXMSNodeEditorWidget::OnSpellEditorComponentSet()
{
}
