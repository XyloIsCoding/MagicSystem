// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XMSNodeCanvasWidget.generated.h"

class UXMSWrapBox;
class UXMSSubNodeWidget;
class UXMSSpellEditorComponent;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeCanvasWidget : public UUserWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UUserWidget Interface
	 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeCanvasWidget
	 */

public:
	int32 GetNodeWidgetIndex(UXMSSubNodeWidget* NodeWidget);
	int32 AddNodeWidgetAt(int32 Index, UXMSSubNodeWidget* NodeWidget);

public:
	void SetSpellEditorComponent(UXMSSpellEditorComponent* InSpellEditorComponent);
protected:
	virtual void OnSpellEditorComponentSet();
	UPROPERTY()
	TObjectPtr<UXMSSpellEditorComponent> SpellEditorComponent;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UXMSWrapBox> NodesWrapBox;
};
