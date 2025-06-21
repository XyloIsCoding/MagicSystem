// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Value/XMSVariableTypeValueNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSVariableTypeValueNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);

	NodeJson->SetNumberField(ValueJsonKey, VariableType);
	return NodeJson;
}

void UXMSVariableTypeValueNode::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);

	JsonObject->TryGetNumberField(ValueJsonKey, VariableType);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSVariableTypeValueNode
 */

void UXMSVariableTypeValueNode::SetVariableType(int32 InType)
{
	VariableType = InType;
}
