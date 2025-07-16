// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Float/Operation/XMSFloatOperationNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSFloatValueInterface Interface
 */

bool UXMSFloatOperationNode::GetFloat(float& OutFloat)
{
	if (IXMSFloatOperatorInterface* FloatOperatorInterface = FloatOperator.GetInterface())
	{
		return FloatOperatorInterface->ApplyFloatOperation(OutFloat);
	}
	return false;
}