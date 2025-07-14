// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeTooltipWidget.h"
#include "XMSNodeDoubleTooltipWidget.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeDoubleTooltipWidget : public UXMSNodeTooltipWidget
{
	GENERATED_BODY()

public:
	virtual void ClearTooltip() override;
	
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<URichTextBlock> SubTitle;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<URichTextBlock> SubBody;
};
