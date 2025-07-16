// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Rotator/Operation/XMSRotatorOperationNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSRotatorValueInterface Interface
 */

bool UXMSRotatorOperationNode::GetRotator(FRotator& OutRotator)
{
	if (IXMSRotatorOperatorInterface* RotatorOperatorInterface = RotatorOperator.GetInterface())
	{
		return RotatorOperatorInterface->ApplyRotatorOperation(OutRotator);
	}
	return false;
}