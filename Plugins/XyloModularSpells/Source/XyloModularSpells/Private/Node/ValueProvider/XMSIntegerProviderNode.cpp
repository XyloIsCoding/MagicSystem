// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/ValueProvider/XMSIntegerProviderNode.h"

#include "Node/Value/XMSIntegerValueNodeInterface.h"
#include "Node/Value/XMSValueNode.h"

int32 UXMSIntegerProviderNode::GetIntegerValue() const
{
	if (IsValid(IntegerNode))
	{
		if (IXMSIntegerValueNodeInterface* StringValueInterface = Cast<IXMSIntegerValueNodeInterface>(IntegerNode))
		{
			return StringValueInterface->GetIntegerValue();
		}
	}
	return 0;
}
