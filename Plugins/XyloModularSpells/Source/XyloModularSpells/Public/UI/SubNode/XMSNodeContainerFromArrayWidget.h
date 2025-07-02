// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeContainerWidget.h"
#include "XMSNodeContainerFromArrayWidget.generated.h"

class UXMSNodeIconWidget;
class UXMSNodeWithArray;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeContainerFromArrayWidget : public UXMSNodeContainerWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeCanvasEntryWidget
	 */

/*--------------------------------------------------------------------------------------------------------------------*/
	// Event
	
protected:
	virtual void OnOwningNodeRemovedFromParent() override;

	// ~Event
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// OwningNode
	
protected:
	virtual void OnOwningNodeSet() override;

	// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeContainerFromArrayWidget
	 */

protected:
	UFUNCTION(BlueprintCallable)
	void RemoveSubNode();
	UFUNCTION(BlueprintCallable)
	void InsertSubNode();

/*--------------------------------------------------------------------------------------------------------------------*/
	// Events

private:
	void OnOwningNodeSubNodeAdded(const FXMSNodePathElement& PathElement);
	void OnOwningNodeSubNodeRemoved(const FXMSNodePathElement& PathElement);
	FDelegateHandle OnOwningNodeSubNodeAddedHandle;
	FDelegateHandle OnOwningNodeSubNodeRemovedHandle;

	// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

	
};
