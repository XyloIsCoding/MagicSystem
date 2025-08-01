// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Integer/XMSIntegerValueNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSIntegerValueNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);

	NodeJson->SetNumberField(ValueJsonKey, Integer);
	return NodeJson;
}

void UXMSIntegerValueNode::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);
	
	JsonObject->TryGetNumberField(ValueJsonKey, Integer);
}

bool UXMSIntegerValueNode::GetInteger(int32& OutInteger)
{
	OutInteger = Integer;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSIntegerValueNode
 */

void UXMSIntegerValueNode::SetInteger(int32 InInteger)
{
	int32 OldInteger = Integer;
	Integer = InInteger;

	IntegerValueChangedDelegate.Broadcast(Integer, OldInteger);
}
