// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NodeTooltip/XMSNodeTooltipWidget.h"

#include "Components/RichTextBlock.h"

void UXMSNodeTooltipWidget::ClearTooltip()
{
	Title->SetText(FText::FromString(FString()));
	Body->SetText(FText::FromString(FString()));
}
