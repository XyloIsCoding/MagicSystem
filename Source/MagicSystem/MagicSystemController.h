// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MagicSystemController.generated.h"

/**
 * 
 */
UCLASS()
class MAGICSYSTEM_API AMagicSystemController : public APlayerController
{
	GENERATED_BODY()

	virtual void OnPossess(APawn* InPawn) override;
};
