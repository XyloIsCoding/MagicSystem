// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSSubNodeWidget.h"
#include "XMSArraySubNodeWidget.generated.h"

class UXMSNodeIconWidget;
class UXMSNodeWithArray;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSArraySubNodeWidget : public UXMSSubNodeWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSSubNodeWidget
	 */

/*--------------------------------------------------------------------------------------------------------------------*/
	// Events

protected:
	virtual void OnSubNodeChanged(const FXMSNodePathElement& PathElement) override;

	// ~Events
/*--------------------------------------------------------------------------------------------------------------------*/
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSArraySubNodeWidget
	 */

public:
	UFUNCTION(BlueprintCallable)
	virtual void UpdateSubNodeClassIcon();
protected:
	UPROPERTY(meta = (BindWidget))
	UXMSNodeIconWidget* NodeClassIcon;

protected:
	UFUNCTION(BlueprintCallable)
	void RemoveSubNode();
	UFUNCTION(BlueprintCallable)
	void InsertSubNode();
	
};
