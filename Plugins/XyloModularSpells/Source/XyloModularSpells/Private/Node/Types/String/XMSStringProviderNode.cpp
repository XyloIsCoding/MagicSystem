// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/String/XMSStringProviderNode.h"

#include "Node/Types/Integer/XMSIntegerValueNode.h"
#include "Node/Types/String/XMSStringValueNode.h"

UXMSStringProviderNode::UXMSStringProviderNode()
{
	
}

bool UXMSStringProviderNode::GetString(FString& OutString)
{
	IXMSStringValueInterface* StringValueInterface = StringNode.GetInterface();
	if (!StringValueInterface)
	{
		OutString = FString(TEXT("ERROR: UXMSStringProviderNode::GetString >> Failed to get string!"));
		return false;
	}
	
	return StringValueInterface->GetString(OutString);
}
