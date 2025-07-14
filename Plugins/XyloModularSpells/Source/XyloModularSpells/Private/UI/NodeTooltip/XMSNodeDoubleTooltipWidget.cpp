// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeTooltip/XMSNodeDoubleTooltipWidget.h"

#include "Components/RichTextBlock.h"

void UXMSNodeDoubleTooltipWidget::ClearTooltip()
{
	Super::ClearTooltip();

	SubTitle->SetText(FText::FromString(FString()));
	SubBody->SetText(FText::FromString(FString()));
}
