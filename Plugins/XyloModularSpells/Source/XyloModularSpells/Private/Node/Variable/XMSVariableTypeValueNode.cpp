// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Variable/XMSVariableTypeValueNode.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/XMSNodeDataRegistry.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSVariableTypeValueNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);
	
	NodeJson->SetStringField(ValueJsonKey, VariableType.ToString());
	
	return NodeJson;
}

void UXMSVariableTypeValueNode::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);

	FString VariableTypeString;
	JsonObject->TryGetStringField(ValueJsonKey, VariableTypeString);
	VariableType = UXMSNodeStaticLibrary::GetValueTypeFromName(FName(VariableTypeString));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSVariableTypeValueNode
 */

void UXMSVariableTypeValueNode::GetPossibleTypes(TArray<FGameplayTag>& OutTypes)
{
	UXMSNodeStaticLibrary::GetAllValueTypes(OutTypes);
}

void UXMSVariableTypeValueNode::SetVariableType(const FGameplayTag& InType)
{
	FGameplayTag OldType = VariableType;
	VariableType = InType;
	
	VariableTypeChangedDelegate.Broadcast(VariableType, OldType);
}
