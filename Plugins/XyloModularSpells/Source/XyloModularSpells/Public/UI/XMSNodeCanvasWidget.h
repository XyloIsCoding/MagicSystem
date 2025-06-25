// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XMSNodeCanvasWidget.generated.h"

class UXMSNodeWidget;
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
	UFUNCTION(BlueprintImplementableEvent)
	void AddNodeWidget(UXMSNodeWidget* NodeWidget);

public:
	void SetSpellEditorComponent(UXMSSpellEditorComponent* InSpellEditorComponent);
protected:
	virtual void OnSpellEditorComponentSet();
	UPROPERTY()
	TObjectPtr<UXMSSpellEditorComponent> SpellEditorComponent;
};
