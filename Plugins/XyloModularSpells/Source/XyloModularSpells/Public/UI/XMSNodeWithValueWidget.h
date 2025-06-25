// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeWidget.h"
#include "XMSNodeWithValueWidget.generated.h"

class UXMSNodeWithValue;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeWithValueWidget : public UXMSNodeWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UUserWidget Interface
	 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeWidget
	 */

protected:
	virtual void OnSpellEditorComponentSet() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeWithValueWidget
	 */

public:
	void SetNode(UXMSNodeWithValue* OwningNode);
protected:
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeWithValue> Node;
};
