// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Operation/XMSIntegerOperationNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSIntegerValueInterface Interface
 */

int32 UXMSIntegerOperationNode::GetInteger()
{
	if (IXMSIntegerOperatorInterface* IntegerOperatorInterface = IntegerOperator.Get())
	{
		return IntegerOperatorInterface->ApplyIntegerOperation();
	}
	return 0;
}
