// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Instruction/XMSInstructionNode.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithArray.h"
#include "XMSProgramNode.generated.h"

class IXMSRunnableNodeInterface;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSProgramNode : public UXMSNodeWithArray
{
	GENERATED_BODY()

public:
	UXMSProgramNode();

private:
	TXMSMultiNodeContainer<UXMSInstructionNode, IXMSRunnableNodeInterface> Instructions = { this, FString(TEXT("Instructions")),
		[](UClass* NodeClass){ return true; } };
};
