// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSRunnableNodeInterface.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "XMSRootInstructionNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSRootInstructionNode : public UXMSNodeWithMap, public IXMSRunnableNodeInterface
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSRunnableNodeInterface Interface
	 */

public:
	virtual int32 ExecuteNode() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSProgramNode
	 */
	
public:
	TXMSNodeContainer<UXMSNode, IXMSRunnableNodeInterface> Instruction = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, Instruction),
		[](UClass* NodeClass){ return true; } };
};
