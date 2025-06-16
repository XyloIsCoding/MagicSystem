// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Runnable/XMSRunnableNodeInterface.h"
#include "XMSInstructionNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSInstructionNode : public UXMSNodeWithMap, public IXMSRunnableNodeInterface
{
	GENERATED_BODY()
};
