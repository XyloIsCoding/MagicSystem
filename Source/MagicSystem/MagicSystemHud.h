// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MagicSystemHud.generated.h"

class UXMSNodeCanvasWidget;

/**
 * 
 */
UCLASS()
class MAGICSYSTEM_API AMagicSystemHud : public AHUD
{
	GENERATED_BODY()

	virtual void DrawHUD() override;

public:
	UPROPERTY()
	TWeakObjectPtr<UXMSNodeCanvasWidget> NodeCanvasWidget;
};
