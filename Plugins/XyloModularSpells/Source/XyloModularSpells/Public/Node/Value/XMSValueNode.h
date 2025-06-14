// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/Base/XMSNode.h"
#include "UObject/Object.h"
#include "XMSValueNode.generated.h"

/**
 * Value Nodes contain a raw value of their type, and should only implement the interface for their value!
 */
UCLASS(Abstract)
class XYLOMODULARSPELLS_API UXMSValueNode : public UXMSNode
{
	GENERATED_BODY()
};
