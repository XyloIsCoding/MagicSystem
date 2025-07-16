// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSRotatorOperatorInterface.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Types/Rotator/XMSRotatorValueInterface.h"
#include "XMSRotatorOperationNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSRotatorOperationNode : public UXMSNodeWithMap, public IXMSRotatorValueInterface
{
	GENERATED_BODY()
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSRotatorValueInterface Interface
	 */
	
public:
	virtual bool GetRotator(FRotator& OutRotator) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSIntegerOperationNode
	 */
	
public:
	TXMSNodeContainer<UXMSNode, IXMSRotatorOperatorInterface> RotatorOperator = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, RotatorOperator),
		[](UClass* NodeClass){ return true; } };
};
