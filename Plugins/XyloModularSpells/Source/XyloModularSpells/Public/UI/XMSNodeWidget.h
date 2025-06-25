// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XMSNodeWidget.generated.h"

class UXMSSpellEditorComponent;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UXMSNodeWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UUserWidget Interface
	 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeWidget
	 */

public:
	void SetSpellEditorComponent(UXMSSpellEditorComponent* InSpellEditorComponent);
protected:
	virtual void OnSpellEditorComponentSet();
	UPROPERTY()
	TObjectPtr<UXMSSpellEditorComponent> SpellEditorComponent;
	
};
