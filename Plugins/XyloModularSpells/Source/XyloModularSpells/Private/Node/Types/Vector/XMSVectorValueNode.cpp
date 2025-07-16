// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Vector/XMSVectorValueNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSVectorValueNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);

	NodeJson->SetNumberField(FString(TEXT("X")), Vector.X);
	NodeJson->SetNumberField(FString(TEXT("Y")), Vector.Y);
	NodeJson->SetNumberField(FString(TEXT("Z")), Vector.Z);
	return NodeJson;
}

void UXMSVectorValueNode::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);
	
	JsonObject->TryGetNumberField(FString(TEXT("X")), Vector.X);
	JsonObject->TryGetNumberField(FString(TEXT("Y")), Vector.Y);
	JsonObject->TryGetNumberField(FString(TEXT("Z")), Vector.Z);
}

bool UXMSVectorValueNode::GetVector(FVector& OutVector)
{
	OutVector = Vector;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSVectorValueNode
 */

void UXMSVectorValueNode::SetVector(FVector InVector)
{
	FVector OldVector = Vector;
	Vector = InVector;

	VectorValueChangedDelegate.Broadcast(Vector, OldVector);
}
