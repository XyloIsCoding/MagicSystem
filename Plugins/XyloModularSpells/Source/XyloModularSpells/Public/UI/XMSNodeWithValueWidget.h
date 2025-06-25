// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSSubNodeWidget.h"
#include "XMSNodeWithValueWidget.generated.h"

class UXMSNodeWithValue;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeWithValueWidget : public UXMSSubNodeWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UUserWidget Interface
	 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSSubNodeWidget
	 */

protected:
	virtual void OnSpellEditorComponentSet() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeWithValueWidget
	 */

public:
	void SetValueNode(UXMSNodeWithValue* OwningNode);
protected:
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeWithValue> ValueNode;
};
