// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSFloatOperatorInterface.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Types/Float/XMSFloatValueInterface.h"
#include "XMSFloatOperationNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSFloatOperationNode : public UXMSNodeWithMap, public IXMSFloatValueInterface
{
	GENERATED_BODY()
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSFloatValueInterface Interface
	 */
	
public:
	virtual bool GetFloat(float& OutFloat) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSIntegerOperationNode
	 */
	
public:
	TXMSNodeContainer<UXMSNode, IXMSFloatOperatorInterface> FloatOperator = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, FloatOperator),
		[](UClass* NodeClass){ return true; } };
};
