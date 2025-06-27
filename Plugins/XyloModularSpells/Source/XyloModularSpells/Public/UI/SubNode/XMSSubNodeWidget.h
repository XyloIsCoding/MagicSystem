// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSTypes.h"
#include "Blueprint/UserWidget.h"
#include "XMSSubNodeWidget.generated.h"

class UXMSNodeCanvasWidget;
struct FXMSNodePathElement;
class UXMSNode;
class UXMSSubNodeWidget;

DECLARE_MULTICAST_DELEGATE_TwoParams(FXMSSubNodeWidgetUpdatedSignature, UXMSSubNodeWidget*, UXMSNode*)
DECLARE_MULTICAST_DELEGATE_OneParam(FXMSSubNodeWidgetClickedSignature, UXMSSubNodeWidget*)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSSubNodeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UXMSSubNodeWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSSubNodeWidget
	 */

public:
	UFUNCTION(BlueprintCallable)
	virtual FString GetCurrentNodeSelectionName() const;

public:
	UXMSNode* GetSubNode() const;
	virtual void GetSubNodeClassOptions(TArray<UClass*>& OutClassOptions);
protected:
	virtual void ResetSubNodeIcon();
	virtual void UpdateSubNodeIcon(UXMSNode& SubNode);
	
/*--------------------------------------------------------------------------------------------------------------------*/
	// Events

public:
	FXMSSubNodeWidgetClickedSignature SubNodeClickedDelegate;
	FXMSSubNodeWidgetUpdatedSignature SubNodeChangedDelegate;
	UFUNCTION(BlueprintCallable)
	void BroadcastSubNodeClicked();
protected:
	virtual void OnOwningNodeRemovedFromParent();
	virtual void OnSubNodeChanged(const FXMSNodePathElement& PathElement);

	// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// OwningNode
	
public:
	void SetOwningNode(UXMSNode* InOwningNode, const FXMSNodePathElement& PathFromOwningNode);
	UXMSNode* GetParentNode() const;
	const FXMSNodePathElement& GetPathFromParent() const;
protected:
	virtual void OnOwningNodeSet();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningNodeSet();
	UPROPERTY()
	TWeakObjectPtr<UXMSNode> OwningNode;
	FXMSNodePathElement ThisNodePath;

	// ~OwningNode
/*--------------------------------------------------------------------------------------------------------------------*/
	
};
