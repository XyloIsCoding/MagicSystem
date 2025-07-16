// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Bool/XMSBoolValueNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSBoolValueNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);

	NodeJson->SetBoolField(ValueJsonKey, Bool);
	return NodeJson;
}

void UXMSBoolValueNode::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);
	
	JsonObject->TryGetBoolField(ValueJsonKey, Bool);
}

bool UXMSBoolValueNode::GetBool(bool& OutBool)
{
	OutBool = Bool;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSBoolValueNode
 */

void UXMSBoolValueNode::SetBool(bool InBool)
{
	bool OldBool = Bool;
	Bool = InBool;

	BoolValueChangedDelegate.Broadcast(Bool, OldBool);
}
