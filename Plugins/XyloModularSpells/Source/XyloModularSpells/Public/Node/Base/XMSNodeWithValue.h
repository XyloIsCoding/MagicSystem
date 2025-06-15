// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNode.h"
#include "XMSNodeWithValue.generated.h"

/**
 * Value Nodes contain a raw value of their type, and should only implement the interface for their value!
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeWithValue : public UXMSNode
{
	GENERATED_BODY()
};
