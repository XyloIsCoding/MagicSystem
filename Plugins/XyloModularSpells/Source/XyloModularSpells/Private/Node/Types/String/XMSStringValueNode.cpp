// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/String/XMSStringValueNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSStringValueNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);

	NodeJson->SetStringField(ValueJsonKey, String);
	return NodeJson;
}

void UXMSStringValueNode::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);

	JsonObject->TryGetStringField(ValueJsonKey, String);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSStringValueInterface Interface
 */

bool UXMSStringValueNode::GetString(FString& OutString)
{
	OutString = String;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSStringValueNode
 */

void UXMSStringValueNode::SetString(const FString& InString)
{
	FString OldString = String;
	String = InString;

	StringValueChangedDelegate.Broadcast(String, OldString);
}
