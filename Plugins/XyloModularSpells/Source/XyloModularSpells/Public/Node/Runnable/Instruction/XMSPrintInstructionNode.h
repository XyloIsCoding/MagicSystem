// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Runnable/XMSRunnableNodeInterface.h"
#include "Node/Value/XMSStringValueInterface.h"
#include "XMSPrintInstructionNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSPrintInstructionNode : public UXMSNodeWithMap, public IXMSRunnableNodeInterface
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
	TXMSNodeContainer<UXMSNode, IXMSStringValueInterface> OutputString = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, OutputString),
		[](UClass* NodeClass){ return true; } };
};
