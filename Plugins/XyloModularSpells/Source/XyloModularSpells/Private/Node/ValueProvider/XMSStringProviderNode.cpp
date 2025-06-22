// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/ValueProvider/XMSStringProviderNode.h"

#include "Node/Value/XMSIntegerValueNode.h"
#include "Node/Value/XMSStringValueNode.h"

UXMSStringProviderNode::UXMSStringProviderNode()
{
	
}

bool UXMSStringProviderNode::GetString(FString& OutString)
{
	IXMSStringValueInterface* StringValueInterface = StringNode.Get();
	if (!StringValueInterface)
	{
		OutString = FString(TEXT("ERROR: UXMSStringProviderNode::GetString >> Failed to get string!"));
		return false;
	}
	
	return StringValueInterface->GetString(OutString);
}
