// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/NodeTooltip/XMSNodeTooltipInterface.h"
#include "XMSNodeCanvasEntryWidget.generated.h"

class UXMSNode;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeCanvasEntryWidget : public UUserWidget, public IXMSNodeTooltipInterface
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSNodeTooltipInterface Interface
	 */

public:
	UFUNCTION(BlueprintCallable)
	void BroadcastTooltipRequestedDelegate();
	FXMSTooltipRequestedSignature TooltipRequestedDelegate;
	virtual FXMSTooltipRequestedSignature& GetTooltipRequestedDelegate() override { return TooltipRequestedDelegate; }
	virtual void InitializeTooltip(UXMSNodeTooltipWidget* TooltipWidget) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeCanvasEntryWidget
	 */

/*--------------------------------------------------------------------------------------------------------------------*/
	// Events

protected:
	/** This function is called when the OwningNode is no longer part of the spell hierarchy.
	 * This means that all its NodeContainers do no longer need widgets to be represented visually, so we remove
	 * this widget from canvas.
	 * @note This function should also unbind any delegate bound to OwningNode, since it is used by widgets like
	 * XMSNodeContainerFromArrayWidget to remove themselves while parent is still in hierarchy. */
	virtual void OnOwningNodeRemovedFromParent();
private:
	FDelegateHandle OnOwningNodeRemovedFromParentHandle;

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
