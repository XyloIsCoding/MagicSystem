// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XMSNodeCanvasEntryWidget.generated.h"

class UXMSNode;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeCanvasEntryWidget : public UUserWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeCanvasEntryWidget
	 */

/*--------------------------------------------------------------------------------------------------------------------*/
	// Events

protected:
	virtual void OnOwningNodeRemovedFromParent();

	// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/
	
/*--------------------------------------------------------------------------------------------------------------------*/
	// OwningNode
	
public:
	void SetOwningNode(UXMSNode* InOwningNode);
protected:
	virtual void OnOwningNodeSet();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningNodeSet();
	UPROPERTY()
	TWeakObjectPtr<UXMSNode> OwningNode;

	// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/
	
};
