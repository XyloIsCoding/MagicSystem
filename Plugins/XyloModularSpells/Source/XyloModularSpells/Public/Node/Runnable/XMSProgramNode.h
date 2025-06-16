// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSRunnableNodeInterface.h"
#include "Instruction/XMSInstructionNode.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithArray.h"
#include "XMSProgramNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSProgramNode : public UXMSNodeWithArray
{
	GENERATED_BODY()

public:
	UXMSProgramNode();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSProgramNode
	 */
	
public:
	TXMSMultiNodeContainer<UXMSInstructionNode, IXMSRunnableNodeInterface> Instructions = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, Instructions),
		[](UClass* NodeClass){ return true; } };
};
