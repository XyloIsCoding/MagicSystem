// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Base/XMSNodeWithValue.h"


const FString UXMSNodeWithValue::ValueJsonKey = FString(TEXT("Value"));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// Serialization

TSharedPtr<FJsonObject> UXMSNodeWithValue::SerializeToJson(bool& bOutSuccess)
{
	return Super::SerializeToJson(bOutSuccess);
}

void UXMSNodeWithValue::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);
}

// ~Serialization
/*--------------------------------------------------------------------------------------------------------------------*/

