// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicSystemHud.h"

#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/Widget.h"
#include "UI/XMSNodeCanvasWidget.h"
#include "UI/BaseWidget/XMSWrapBox.h"

void AMagicSystemHud::DrawHUD()
{
	Super::DrawHUD();
	
	UXMSNodeCanvasWidget* Canvas = NodeCanvasWidget.Get();
	if (Canvas)
	{
		Canvas->ForceLayoutPrepass();
		for (UWidget* Entry : Canvas->NodesWrapBox->GetAllChildren())
		{
			FVector2D PixelPos;
			FVector2D ViewportPos;
			USlateBlueprintLibrary::LocalToViewport(this, Entry->GetCachedGeometry(), FVector2D(0.0f, 0.0f), PixelPos, ViewportPos);
			DrawRect(FLinearColor::Red, ViewportPos.X, ViewportPos.Y, 5.0f, 5.0f);
		}
	}
}
