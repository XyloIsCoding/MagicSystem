// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Base/XMSNode.h"


const FString UXMSNode::NodeClassJsonKey = FString(TEXT("NodeClass"));

UXMSNode::UXMSNode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

TSharedPtr<FJsonObject> UXMSNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = MakeShareable<>(new FJsonObject);
	NodeJson->SetStringField(NodeClassJsonKey, GetClass()->GetName());
	bOutSuccess = true;
	return NodeJson;
}

void UXMSNode::DeserializeFromJson(TSharedPtr<FJsonObject>)
{
	
}


