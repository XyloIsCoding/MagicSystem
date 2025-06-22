// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Operation/XMSStringOperationNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSStringValueInterface Interface
 */

bool UXMSStringOperationNode::GetString(FString& OutString)
{
	IXMSStringOperatorInterface* StringOperatorInterface = StringOperator.Get();
	if (!StringOperatorInterface)
	{
		OutString = FString(TEXT("ERROR: UXMSStringOperationNode::GetString >> Failed to get string!"));
		return false;
	}
	
	OutString = StringOperatorInterface->ApplyStringOperation();
	return true;
}
