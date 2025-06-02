// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/ValueProvider/XMSStringProviderNode.h"

#include "Node/Value/XMSValueNode.h"

FString UXMSStringProviderNode::GetStringValue() const
{
	if (IsValid(StringNode))
	{
		if (IXMSStringValueNodeInterface* StringValueInterface = Cast<IXMSStringValueNodeInterface>(StringNode))
		{
			return StringValueInterface->GetStringValue();
		}
	}
	return FString();
}
