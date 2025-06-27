// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSTypes.h"
#include "UI/XMSNodeEditorWidget.h"
#include "XMSSubNodeWidget.generated.h"

struct FXMSNodePathElement;
class UXMSNode;
class UXMSSpellEditorComponent;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSSubNodeWidget : public UXMSNodeEditorWidget
{
	GENERATED_BODY()

public:
	UXMSSubNodeWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeEditorWidget Interface
	 */

protected:
	virtual void OnSpellEditorComponentSet() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSSubNodeWidget
	 */

public:
	UFUNCTION(BlueprintCallable)
	virtual FString GetCurrentNodeSelectionName() const;
	virtual void GetSubNodeClassOptions(TArray<UClass*>& OutClassOptions);
protected:
	virtual void ResetSubNodeIcon();
	virtual void UpdateSubNodeIcon(UXMSNode& SubNode);
	
/*--------------------------------------------------------------------------------------------------------------------*/
	// Events
	
protected:
	virtual void OnOwningNodeRemovedFromParent();
	virtual void OnSubNodeChanged(const FXMSNodePathElement& PathElement);

	// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// OwningNode
	
public:
	void SetOwningNode(UXMSNode* InOwningNode, const FXMSNodePathElement& PathFromOwningNode);
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
