// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSSubNodeWidget.h"
#include "XMSMapSubNodeWidget.generated.h"

class UXMSNodeIconWidget;
class UXMSNodeWithMap;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSMapSubNodeWidget : public UXMSSubNodeWidget
{
	GENERATED_BODY()
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSMapSubNodeWidget
	 */

public:
	UFUNCTION(BlueprintCallable)
	virtual void UpdateSubNodeClassIcon();
protected:
	UPROPERTY(meta = (BindWidget))
	UXMSNodeIconWidget* NodeClassIcon;

public:
	UFUNCTION(BlueprintCallable)
	virtual void UpdateSubNodeTypeIcon();
protected:
	UPROPERTY(meta = (BindWidget))
	UXMSNodeIconWidget* NodeTypeIcon;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure=false)
	virtual bool GetSubNodeTypeDisplayData(UTexture2D*& OutGlyph, FText& OutDisplayName, FText& OutDescription) const;
	UFUNCTION(BlueprintCallable, BlueprintPure=false)
	virtual UTexture2D* GetSubNodeTypeIcon() const;

};
