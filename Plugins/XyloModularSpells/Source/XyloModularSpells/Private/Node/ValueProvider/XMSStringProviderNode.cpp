// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/ValueProvider/XMSStringProviderNode.h"

#include "Node/Value/XMSIntegerValueNode.h"
#include "Node/Value/XMSStringValueNode.h"

UXMSStringProviderNode::UXMSStringProviderNode()
{
	
}

FString UXMSStringProviderNode::GetString()
{
	IXMSStringValueInterface* StringValueInterface = StringNode.Get();
	if (!StringValueInterface) return FString(TEXT("ERROR: UXMSStringProviderNode::GetString failed!"));
	
	return StringValueInterface->GetString();
}
