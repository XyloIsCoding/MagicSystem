// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSInstructionNode.h"
#include "XMSSpawnShapeInstructionNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSSpawnShapeInstructionNode : public UXMSInstructionNode
{
	GENERATED_BODY()

public:
	virtual void ExecuteNode() override;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ShapeClass;
};
