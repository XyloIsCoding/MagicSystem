// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "XMSNode.generated.h"

struct FXMSMultiNodeContainer;
struct FXMSNodeContainer;

/**
 * 
 */
UCLASS(Abstract)
class XYLOMODULARSPELLS_API UXMSNode : public UObject
{
	GENERATED_BODY()
	
public:
	UXMSNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
};
