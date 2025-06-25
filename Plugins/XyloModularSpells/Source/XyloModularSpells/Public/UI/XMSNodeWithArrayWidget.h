// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeWidget.h"
#include "XMSNodeWithArrayWidget.generated.h"

class UXMSNodeWithArray;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeWithArrayWidget : public UXMSNodeWidget
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
	 * UXMSNodeWithArrayWidget
	 */

public:
	void SetNode(UXMSNodeWithArray* OwningNode);
protected:
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeWithArray> Node;
};
