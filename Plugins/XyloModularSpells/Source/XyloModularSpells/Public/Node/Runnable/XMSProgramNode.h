// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSRunnableNodeInterface.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithArray.h"
#include "XMSProgramNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSProgramNode : public UXMSNodeWithArray, public IXMSRunnableNodeInterface
{
	GENERATED_BODY()

public:
	UXMSProgramNode();

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
	TXMSMultiNodeContainer<UXMSNode, IXMSRunnableNodeInterface> Instructions = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, Instructions),
		[](UClass* NodeClass){ return true; } };
};
