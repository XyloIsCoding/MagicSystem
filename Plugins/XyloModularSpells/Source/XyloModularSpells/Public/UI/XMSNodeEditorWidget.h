// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XMSNodeEditorWidget.generated.h"

class UXMSSpellEditorComponent;

/**
 * Base class for all widgets managed by SpellEditorComponent
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeEditorWidget : public UUserWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeEditorWidget
	 */
	
public:
	void SetSpellEditorComponent(UXMSSpellEditorComponent* InSpellEditorComponent);
protected:
	virtual void OnSpellEditorComponentSet();
	UPROPERTY()
	TWeakObjectPtr<UXMSSpellEditorComponent> SpellEditorComponent;
};
