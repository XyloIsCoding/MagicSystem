// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeContainerWidget.h"
#include "XMSNodeContainerFromMapWidget.generated.h"

class UXMSNodeIconWidget;
class UXMSNodeWithMap;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeContainerFromMapWidget : public UXMSNodeContainerWidget
{
	GENERATED_BODY()
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeContainerFromMapWidget
	 */

/*--------------------------------------------------------------------------------------------------------------------*/
	// Icon

public:
	UFUNCTION(BlueprintCallable)
	virtual void UpdateSubNodeTypeIcon();
	UFUNCTION(BlueprintCallable, BlueprintPure=false)
	virtual bool GetSubNodeTypeDisplayData(UTexture2D*& OutGlyph, FText& OutDisplayName, FText& OutDescription) const;
	UFUNCTION(BlueprintCallable, BlueprintPure=false)
	virtual UTexture2D* GetSubNodeTypeIcon() const;
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeIconWidget> NodeTypeIcon;

	// ~Icon
/*--------------------------------------------------------------------------------------------------------------------*/

};
