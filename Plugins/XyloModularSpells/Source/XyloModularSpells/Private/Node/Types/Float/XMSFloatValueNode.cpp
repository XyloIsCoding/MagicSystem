// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Float/XMSFloatValueNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSFloatValueNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);

	NodeJson->SetNumberField(ValueJsonKey, Float);
	return NodeJson;
}

void UXMSFloatValueNode::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);
	
	JsonObject->TryGetNumberField(ValueJsonKey, Float);
}

bool UXMSFloatValueNode::GetFloat(float& OutFloat)
{
	OutFloat = Float;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSFloatValueNode
 */

void UXMSFloatValueNode::SetFloat(float InFloat)
{
	float OldFloat = Float;
	Float = InFloat;

	FloatValueChangedDelegate.Broadcast(Float, OldFloat);
}
