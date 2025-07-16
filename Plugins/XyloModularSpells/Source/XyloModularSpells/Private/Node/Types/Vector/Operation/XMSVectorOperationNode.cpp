// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Vector/Operation/XMSVectorOperationNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSVectorValueInterface Interface
 */

bool UXMSVectorOperationNode::GetVector(FVector& OutVector)
{
	if (IXMSVectorOperatorInterface* VectorOperatorInterface = VectorOperator.GetInterface())
	{
		return VectorOperatorInterface->ApplyVectorOperation(OutVector);
	}
	return false;
}