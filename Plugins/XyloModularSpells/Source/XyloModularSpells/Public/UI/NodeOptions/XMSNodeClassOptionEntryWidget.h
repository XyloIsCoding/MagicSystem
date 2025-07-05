// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeOptionEntryWidget.h"
#include "XMSNodeClassOptionEntryWidget.generated.h"

class UXMSNodeIconWidget;
class UXMSNode;

DECLARE_MULTICAST_DELEGATE_OneParam(FXMSNodeClassOptionSelectedSignature, TSubclassOf<UXMSNode>)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeClassOptionEntryWidget : public UXMSNodeOptionEntryWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeOptionEntryWidget Interface
	 */
	
public:
	virtual void InitializeOption(int32 InOptionIndex) override;
	virtual void BroadcastOptionSelectedDelegate() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeClassOptionEntryWidget
	 */

public:
	FXMSNodeClassOptionSelectedSignature NodeClassOptionSelectedDelegate;
	void SetNodeClass(TSubclassOf<UXMSNode> InNodeClass);
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeIconWidget> NodeClassIcon;
	TSubclassOf<UXMSNode> NodeClass;
};
