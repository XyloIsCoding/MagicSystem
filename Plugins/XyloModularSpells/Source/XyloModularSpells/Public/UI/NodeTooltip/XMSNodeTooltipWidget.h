// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XMSNodeTooltipWidget.generated.h"

class URichTextBlock;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeTooltipWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<URichTextBlock> Title;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<URichTextBlock> Body;
};
