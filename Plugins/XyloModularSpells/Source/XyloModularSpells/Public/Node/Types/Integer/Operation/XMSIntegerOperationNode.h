// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/Types/Integer/Operation/XMSIntegerOperatorInterface.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Types/Integer/XMSIntegerValueInterface.h"
#include "XMSIntegerOperationNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSIntegerOperationNode : public UXMSNodeWithMap, public IXMSIntegerValueInterface
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSIntegerValueInterface Interface
	 */
	
public:
	virtual bool GetInteger(int32& OutInteger) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSIntegerOperationNode
	 */
	
public:
	TXMSNodeContainer<UXMSNode, IXMSIntegerOperatorInterface> IntegerOperator = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, IntegerOperator),
		[](UClass* NodeClass){ return true; } };
};
