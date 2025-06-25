// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSSubNodeWidget.h"
#include "XMSNodeValueWidget.generated.h"

class UXMSNodeWithValue;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeValueWidget : public UXMSSubNodeWidget
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
	 * UXMSNodeValueWidget
	 */

public:
	void SetValueNode(UXMSNodeWithValue* OwningNode);
protected:
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeWithValue> ValueNode;
};
