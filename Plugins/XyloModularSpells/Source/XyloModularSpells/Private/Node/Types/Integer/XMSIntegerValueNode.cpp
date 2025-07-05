// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Value/XMSIntegerValueNode.h"


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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSIntegerValueNode
 */

void UXMSIntegerValueNode::SetInteger(int32 InInteger)
{
	Integer = InInteger;
}
