// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "XMSNode.generated.h"

struct FXMSMultiNodeContainer;
struct FXMSNodeContainer;

/**
 * Use TXMSNodeContainer to add a sub-node.
 * It is preferable to make sub-nodes private, and access them through GetSubNode and SetSubNode
 */
UCLASS(Abstract)
class XYLOMODULARSPELLS_API UXMSNode : public UObject
{
	GENERATED_BODY()
	
public:
	UXMSNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
};
