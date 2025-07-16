// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Bool/Operation/XMSBoolOperationNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSBoolValueInterface Interface
 */

bool UXMSBoolOperationNode::GetBool(bool& OutBool)
{
	if (IXMSBoolOperatorInterface* BoolOperatorInterface = BoolOperator.GetInterface())
	{
		return BoolOperatorInterface->ApplyBoolOperation(OutBool);
	}
	return false;
}