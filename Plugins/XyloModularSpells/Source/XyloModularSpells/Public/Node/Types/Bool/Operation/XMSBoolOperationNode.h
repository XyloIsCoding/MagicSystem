// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSBoolOperatorInterface.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Types/Bool/XMSBoolValueInterface.h"
#include "XMSBoolOperationNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSBoolOperationNode : public UXMSNodeWithMap, public IXMSBoolValueInterface
{
	GENERATED_BODY()
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSBoolValueInterface Interface
	 */
	
public:
	virtual bool GetBool(bool& OutBool) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSIntegerOperationNode
	 */
	
public:
	TXMSNodeContainer<UXMSNode, IXMSBoolOperatorInterface> BoolOperator = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, BoolOperator),
		[](UClass* NodeClass){ return true; } };
};
