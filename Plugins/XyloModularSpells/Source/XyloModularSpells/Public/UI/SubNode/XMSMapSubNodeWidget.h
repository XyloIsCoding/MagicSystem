// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSSubNodeWidget.h"
#include "XMSMapSubNodeWidget.generated.h"

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
	UFUNCTION(BlueprintCallable, BlueprintPure=false)
	virtual bool GetSubNodeTypeDisplayData(UTexture2D*& OutGlyph, FText& OutDisplayName, FText& OutDescription) const;

};
