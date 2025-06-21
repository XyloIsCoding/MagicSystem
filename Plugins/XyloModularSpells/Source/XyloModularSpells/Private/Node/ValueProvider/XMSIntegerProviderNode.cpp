// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/ValueProvider/XMSIntegerProviderNode.h"

UXMSIntegerProviderNode::UXMSIntegerProviderNode()
{
	
}

int32 UXMSIntegerProviderNode::GetInteger()
{
	IXMSIntegerValueInterface* IntegerValueInterface = IntegerNode.Get();
	if (!IntegerValueInterface) return 0;
	
	return IntegerValueInterface->GetInteger();
}

FString UXMSIntegerProviderNode::GetString(bool& bOutResult)
{
	return FString::FromInt(GetInteger());
}
