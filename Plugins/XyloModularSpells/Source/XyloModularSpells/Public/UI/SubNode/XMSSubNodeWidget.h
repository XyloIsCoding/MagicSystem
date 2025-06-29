// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSTypes.h"
#include "UI/BaseWidget/XMSNodeCanvasEntryWidget.h"
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
class XYLOMODULARSPELLS_API UXMSSubNodeWidget : public UXMSNodeCanvasEntryWidget
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
	UFUNCTION(BlueprintCallable, BlueprintPure=false)
	virtual bool GetSubNodeDisplayData(UTexture2D*& OutGlyph, FText& OutDisplayName, FText& OutDescription) const;

public:
	UXMSNode* GetSubNode() const;
	virtual void GetSubNodeClassOptions(TArray<UClass*>& OutClassOptions);
	void ChangeSubNodeClass(UClass* NewClass);
protected:
	virtual void ResetSubNodeIcon();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_ResetSubNodeIcon();
	virtual void UpdateSubNodeIcon(UXMSNode* SubNode);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpdateSubNodeIcon(UXMSNode* SubNode);
	
/*--------------------------------------------------------------------------------------------------------------------*/
	// Events

public:
	FXMSSubNodeWidgetClickedSignature SubNodeClickedDelegate;
	FXMSSubNodeWidgetUpdatedSignature SubNodeChangedDelegate;
	UFUNCTION(BlueprintCallable)
	void BroadcastSubNodeClicked();
protected:
	virtual void OnSubNodeChanged(const FXMSNodePathElement& PathElement);

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
