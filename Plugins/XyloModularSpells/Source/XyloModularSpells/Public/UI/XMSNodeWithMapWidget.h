// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeWidget.h"
#include "XMSNodeWithMapWidget.generated.h"

class UXMSNodeWithMap;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeWithMapWidget : public UXMSNodeWidget
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
	void SetMapNode(UXMSNodeWithMap* OwningNode);
protected:
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeWithMap> MapNode;
};
