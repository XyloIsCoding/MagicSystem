// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/World.h"
#include "XMSNode.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, DefaultToInstanced, EditInlineNew)
class XYLOMODULARSPELLS_API UXMSNode : public UObject
{
	GENERATED_BODY()

public:
	virtual AActor* GetOwningActor() const;
	virtual UWorld* GetWorld() const override;
	
};
