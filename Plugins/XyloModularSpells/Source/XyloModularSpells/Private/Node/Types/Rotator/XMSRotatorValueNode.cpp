// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Rotator/XMSRotatorValueNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSRotatorValueNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);

	NodeJson->SetNumberField(FString(TEXT("Roll")), Rotator.Roll);
	NodeJson->SetNumberField(FString(TEXT("Pitch")), Rotator.Pitch);
	return NodeJson;
}

void UXMSRotatorValueNode::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);
	
	JsonObject->TryGetNumberField(FString(TEXT("Roll")), Rotator.Roll);
	JsonObject->TryGetNumberField(FString(TEXT("Pitch")), Rotator.Pitch);
}

bool UXMSRotatorValueNode::GetRotator(FRotator& OutRotator)
{
	OutRotator = Rotator;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSRotatorValueNode
 */

void UXMSRotatorValueNode::SetRotator(FRotator InRotator)
{
	FRotator OldRotator = Rotator;
	Rotator = InRotator;

	RotatorValueChangedDelegate.Broadcast(Rotator, OldRotator);
}
