// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Value/XMSIntegerValueNode.h"

int32 UXMSIntegerValueNode::GetIntegerValue() const
{
	return NodeValue;
}

FString UXMSIntegerValueNode::GetStringValue() const
{
	return FString::FromInt(NodeValue);
}
