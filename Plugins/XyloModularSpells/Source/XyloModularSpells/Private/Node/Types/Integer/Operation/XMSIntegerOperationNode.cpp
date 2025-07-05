// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Integer/Operation/XMSIntegerOperationNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSIntegerValueInterface Interface
 */

int32 UXMSIntegerOperationNode::GetInteger()
{
	if (IXMSIntegerOperatorInterface* IntegerOperatorInterface = IntegerOperator.GetInterface())
	{
		return IntegerOperatorInterface->ApplyIntegerOperation();
	}
	return 0;
}
