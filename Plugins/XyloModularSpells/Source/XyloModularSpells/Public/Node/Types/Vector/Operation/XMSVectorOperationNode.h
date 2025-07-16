// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSVectorOperatorInterface.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Types/Vector/XMSVectorValueInterface.h"
#include "XMSVectorOperationNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSVectorOperationNode : public UXMSNodeWithMap, public IXMSVectorValueInterface
{
	GENERATED_BODY()
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSVectorValueInterface Interface
	 */
	
public:
	virtual bool GetVector(FVector& OutVector) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSIntegerOperationNode
	 */
	
public:
	TXMSNodeContainer<UXMSNode, IXMSVectorOperatorInterface> VectorOperator = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, VectorOperator),
		[](UClass* NodeClass){ return true; } };
};
