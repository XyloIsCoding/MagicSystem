// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Variable/XMSValueTypeValueNode.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/XMSNodeDataRegistry.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSValueTypeValueNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);
	
	NodeJson->SetStringField(ValueJsonKey, ValueType.ToString());
	
	return NodeJson;
}

void UXMSValueTypeValueNode::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);

	FString ValueTypeString;
	JsonObject->TryGetStringField(ValueJsonKey, ValueTypeString);
	ValueType = UXMSNodeStaticLibrary::GetValueTypeFromName(FName(ValueTypeString));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSValueTypeValueNode
 */

void UXMSValueTypeValueNode::GetPossibleTypes(TArray<FGameplayTag>& OutTypes)
{
	UXMSNodeStaticLibrary::GetAllValueTypes(OutTypes);
}

void UXMSValueTypeValueNode::SetValueType(const FGameplayTag& InType)
{
	FGameplayTag OldType = ValueType;
	ValueType = InType;
	
	ValueTypeChangedDelegate.Broadcast(ValueType, OldType);
}
