// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSTypes.h"
#include "UI/BaseWidget/XMSNodeCanvasEntryWidget.h"
#include "UI/NodeOptions/XMSNodeOptionsInterface.h"
#include "XMSNodeContainerWidget.generated.h"

class UXMSNodeIconWidget;
class UXMSNodeCanvasWidget;
struct FXMSNodePathElement;
class UXMSNode;
class UXMSNodeContainerWidget;

DECLARE_MULTICAST_DELEGATE_TwoParams(FXMSNodeWidgetUpdatedSignature, UXMSNodeContainerWidget*, UXMSNode*)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FXMSNodeWidgetSubNodeContainerAddedSignature, UXMSNodeContainerWidget*, UXMSNode* /* Parent of Added SubNode */ , const FXMSNodePathElement& /* Path to Added SubNode */)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeContainerWidget : public UXMSNodeCanvasEntryWidget, public IXMSNodeOptionsInterface
{
	GENERATED_BODY()

public:
	UXMSNodeContainerWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeCanvasEntryWidget Interface
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
	 * IXMSNodeOptionsInterface Interface
	 */

public:
	FXMSOptionsRequestedSignature OptionsRequestedDelegate;
	virtual FXMSOptionsRequestedSignature& GetOptionsRequestedDelegate() override;
	virtual void InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget) override;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeContainerWidget
	 */

/*--------------------------------------------------------------------------------------------------------------------*/
	// Icon
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void UpdateNodeClassIcon();
	UFUNCTION(BlueprintCallable, BlueprintPure=false)
	virtual bool GetNodeDisplayData(UTexture2D*& OutGlyph, FText& OutDisplayName, FText& OutDescription) const;
protected:
	virtual void ResetNodeIcon();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_ResetNodeIcon();
	virtual void UpdateNodeIcon(UXMSNode* Node);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpdateNodeIcon(UXMSNode* Node);
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeIconWidget> NodeClassIcon;

	// ~Icon
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// ContainedNode
	
public:
	UFUNCTION(BlueprintCallable)
	virtual FString GetNodeName() const;
public:
	UXMSNode* GetNode() const;
	virtual void GetNodeClassOptions(TArray<UClass*>& OutClassOptions);
	void ChangeNodeClass(TSubclassOf<UXMSNode> NewClass);

	// ~ContainedNode
/*--------------------------------------------------------------------------------------------------------------------*/
	
/*--------------------------------------------------------------------------------------------------------------------*/
	// Events

public:
	FXMSNodeWidgetUpdatedSignature NodeChangedDelegate;
	FXMSNodeWidgetSubNodeContainerAddedSignature SubNodeContainerAddedDelegate;
	UFUNCTION(BlueprintCallable)
	void BroadcastNodeClicked();
protected:
	virtual void OnNodeChanged();
	/** Called if the node in this container is a NodeWithArray, and an element is added to it */
	virtual void OnSubNodeContainerAdded(const FXMSNodePathElement& PathElement);
	/** Called if the node in this container is a NodeWithArray, and an element is removed to it */
	virtual void OnSubNodeContainerRemoved(const FXMSNodePathElement& PathElement);
private:
	void OnOwningNodeSubNodeChanged(const FXMSNodePathElement& PathElement);
	FDelegateHandle OnOwningNodeSubNodeChangedHandle;
	
	// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// OwningNode
	
public:
	void SetOwningNodeAndPath(UXMSNode* InOwningNode, const FXMSNodePathElement& PathFromOwningNode);
protected:
	UPROPERTY(BlueprintReadOnly)
	FXMSNodePathElement ThisNodePath;

	// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/

public:
	/** Reference to the widgets representing the NodeContainers owned by this Node (this Node is the one contained
	 * by this NodeContainer). Put differently these are the NodeContainers that hold the sub-nodes of this Node
	 * This is emptied in OnNodeChanged, filled by NodeCanvas when creating SubNodeContainerWidgets and elements are
	 * removed in OnSubNodeContainerRemoved
	 * The Last element should ALWAYS be the array terminator (XMSArrayAddButtonWidget) */
	TArray<TWeakObjectPtr<UXMSNodeCanvasEntryWidget>> SubNodeContainerWidgets;
	
};
