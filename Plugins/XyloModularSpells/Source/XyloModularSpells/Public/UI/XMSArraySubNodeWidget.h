// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeWidget.h"
#include "XMSArraySubNodeWidget.generated.h"

class UXMSNodeWithArray;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSArraySubNodeWidget : public UXMSNodeWidget
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
	 * UXMSArraySubNodeWidget
	 */

public:
	void SetArrayNode(UXMSNodeWithArray* OwningNode);
protected:
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeWithArray> ArrayNode;
};
