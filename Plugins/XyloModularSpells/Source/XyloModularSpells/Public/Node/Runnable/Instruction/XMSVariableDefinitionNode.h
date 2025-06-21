// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNode.h"
#include "Node/Runnable/XMSRunnableNodeInterface.h"
#include "Node/Value/XMSStringValueInterface.h"
#include "Node/Value/XMSVariableTypeValueInterface.h"
#include "Node/Value/XMSVariableTypeValueNode.h"
#include "XMSVariableDefinitionNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSVariableDefinitionNode : public UXMSNodeWithMap, public  IXMSRunnableNodeInterface
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
	 * UXMSVariableDefinitionNode
	 */
	
public:
	TXMSNodeContainer<UXMSVariableTypeValueNode, IXMSVariableTypeValueInterface> VariableType = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, VariableType),
		[](UClass* NodeClass){ return true; } };

	TXMSNodeContainer<UXMSNode, IXMSStringValueInterface> VariableName = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, VariableName),
		[](UClass* NodeClass){ return true; } };
};
