// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Integer/XMSIntegerProviderNode.h"

UXMSIntegerProviderNode::UXMSIntegerProviderNode()
{
	
}

bool UXMSIntegerProviderNode::GetInteger(int32& OutInteger)
{
	IXMSIntegerValueInterface* IntegerValueInterface = IntegerNode.GetInterface();
	if (!IntegerValueInterface) return false;
	
	return IntegerValueInterface->GetInteger(OutInteger);
}

bool UXMSIntegerProviderNode::GetString(FString& OutString)
{
	int32 Integer;
	if (!GetInteger(Integer)) return false;
	
	OutString = FString::FromInt(Integer);
	return true;
}
