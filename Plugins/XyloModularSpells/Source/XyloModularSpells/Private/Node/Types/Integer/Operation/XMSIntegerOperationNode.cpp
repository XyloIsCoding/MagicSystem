// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Integer/Operation/XMSIntegerOperationNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSIntegerValueInterface Interface
 */

bool UXMSIntegerOperationNode::GetInteger(int32& OutInteger)
{
	if (IXMSIntegerOperatorInterface* IntegerOperatorInterface = IntegerOperator.GetInterface())
	{
		return IntegerOperatorInterface->ApplyIntegerOperation(OutInteger);
	}
	return false;
}
