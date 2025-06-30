// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSTypes.h"
#include "UI/BaseWidget/XMSNodeCanvasEntryWidget.h"
#include "XMSNodeContainerWidget.generated.h"

class UXMSNodeIconWidget;
class UXMSNodeCanvasWidget;
struct FXMSNodePathElement;
class UXMSNode;
class UXMSNodeContainerWidget;

DECLARE_MULTICAST_DELEGATE_TwoParams(FXMSNodeWidgetUpdatedSignature, UXMSNodeContainerWidget*, UXMSNode*)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FXMSNodeWidgetSubNodeContainerAddedSignature, UXMSNodeContainerWidget*, UXMSNode* /* Parent of Added SubNode */ , const FXMSNodePathElement& /* Path to Added SubNode */)
DECLARE_MULTICAST_DELEGATE_OneParam(FXMSNodeWidgetClickedSignature, UXMSNodeContainerWidget*)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeContainerWidget : public UXMSNodeCanvasEntryWidget
{
	GENERATED_BODY()

public:
	UXMSNodeContainerWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeCanvasEntryWidget
	 */

/*--------------------------------------------------------------------------------------------------------------------*/
	// OwningNode
	
protected:
	virtual void OnOwningNodeSet() override;

	// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeContainerWidget
	 */

public:
	UFUNCTION(BlueprintCallable)
	virtual void UpdateNodeClassIcon();
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UXMSNodeIconWidget* NodeClassIcon;

public:
	UFUNCTION(BlueprintCallable)
	virtual FString GetNodeName() const;
	UFUNCTION(BlueprintCallable, BlueprintPure=false)
	virtual bool GetNodeDisplayData(UTexture2D*& OutGlyph, FText& OutDisplayName, FText& OutDescription) const;

public:
	UXMSNode* GetNode() const;
	virtual void GetNodeClassOptions(TArray<UClass*>& OutClassOptions);
	void ChangeNodeClass(UClass* NewClass);
protected:
	virtual void ResetNodeIcon();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_ResetNodeIcon();
	virtual void UpdateNodeIcon(UXMSNode* Node);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpdateNodeIcon(UXMSNode* Node);
	
/*--------------------------------------------------------------------------------------------------------------------*/
	// Events

public:
	FXMSNodeWidgetClickedSignature NodeClickedDelegate;
	FXMSNodeWidgetUpdatedSignature NodeChangedDelegate;
	FXMSNodeWidgetSubNodeContainerAddedSignature SubNodeContainerAddedDelegate;
	UFUNCTION(BlueprintCallable)
	void BroadcastNodeClicked();
protected:
	virtual void OnNodeChanged();
	/** Called if the node in this container is a NodeWithArray, and an element is added to it */
	virtual void OnSubNodeContainerAdded(const FXMSNodePathElement& PathElement);
private:
	void OnOwningNodeSubNodeChanged(const FXMSNodePathElement& PathElement);
	
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
	
};
