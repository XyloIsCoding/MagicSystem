// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSInstructionNodeInterface.h"
#include "Node/XMSNode.h"
#include "XMSInstructionNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSInstructionNode : public UXMSNode, public IXMSInstructionNodeInterface
{
	GENERATED_BODY()

public:
	virtual void ExecuteNode() override {}
};
