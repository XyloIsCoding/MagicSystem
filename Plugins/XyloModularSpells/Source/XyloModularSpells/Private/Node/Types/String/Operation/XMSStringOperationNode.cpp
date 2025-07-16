// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/String/Operation/XMSStringOperationNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSStringValueInterface Interface
 */

bool UXMSStringOperationNode::GetString(FString& OutString)
{
	IXMSStringOperatorInterface* StringOperatorInterface = StringOperator.GetInterface();
	if (!StringOperatorInterface)
	{
		OutString = FString(TEXT("ERROR: UXMSStringOperationNode::GetString >> Failed to get string!"));
		return false;
	}
	
	return StringOperatorInterface->ApplyStringOperation(OutString);
}
