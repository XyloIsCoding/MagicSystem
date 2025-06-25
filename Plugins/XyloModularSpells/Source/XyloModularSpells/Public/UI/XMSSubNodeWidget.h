// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSTypes.h"
#include "Blueprint/UserWidget.h"
#include "XMSSubNodeWidget.generated.h"

struct FXMSNodePathElement;
class UXMSNode;
class UXMSSpellEditorComponent;

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
	 * UUserWidget Interface
	 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSSubNodeWidget
	 */

public:
	UFUNCTION(BlueprintCallable)
	virtual FString GetCurrentNodeSelectionName() const;

public:
	void SetOwningNode(UXMSNode* InOwningNode, const FXMSNodePathElement& PathFromOwningNode);
protected:
	virtual void OnOwningNodeSet();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningNodeSet();
	virtual void OnOwningNodeRemovedFromParent();
	UPROPERTY()
	TWeakObjectPtr<UXMSNode> OwningNode;
	FXMSNodePathElement ThisNodePath;

public:
	void SetSpellEditorComponent(UXMSSpellEditorComponent* InSpellEditorComponent);
protected:
	virtual void OnSpellEditorComponentSet();
	UPROPERTY()
	TObjectPtr<UXMSSpellEditorComponent> SpellEditorComponent;
	
};
