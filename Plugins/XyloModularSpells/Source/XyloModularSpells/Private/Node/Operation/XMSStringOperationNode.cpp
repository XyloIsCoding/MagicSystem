// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Operation/XMSStringOperationNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSStringValueInterface Interface
 */

FString UXMSStringOperationNode::GetString(bool& bOutResult)
{
	if (IXMSStringOperatorInterface* StringOperatorInterface = StringOperator.Get())
	{
		return StringOperatorInterface->ApplyStringOperation();
	}
	return FString(TEXT("ERROR: UXMSStringOperationNode::GetString >> Failed to get string!"));
}
