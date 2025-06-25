// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSSubNodeWidget.h"
#include "XMSMapSubNodeWidget.generated.h"

class UXMSNodeWithMap;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSMapSubNodeWidget : public UXMSSubNodeWidget
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
	 * UXMSArraySubNodeWidget
	 */

public:
	void SetMapNode(UXMSNodeWithMap* OwningNode);
protected:
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeWithMap> MapNode;
};
