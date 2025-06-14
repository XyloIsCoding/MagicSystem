// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/Base/XMSNode.h"
#include "UObject/Object.h"
#include "XMSValueProviderNode.generated.h"

/**
 * Value Provider Nodes should be used as a sort of "cast" between value types.
 * For example an IntegerProvider can implement the string value interface and the float value one, thus giving
 * the ability to use any integer node as a string or float.
 */
UCLASS(Abstract)
class XYLOMODULARSPELLS_API UXMSValueProviderNode : public UXMSNode
{
	GENERATED_BODY()
};
