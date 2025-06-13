// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Base/XMSNode.h"

#include "Node/XMSNodeContainer.h"

UXMSNode::UXMSNode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

UXMSNode* UXMSNode::GetSubNode(const FString& SubNodeName)
{
	FXMSNodeContainer** ContainerPtrPtr = SubNodes.Find(SubNodeName);
	if (!ContainerPtrPtr) return nullptr;

	return (*ContainerPtrPtr)->GetGeneric();
}

void UXMSNode::SetSubNode(const FString& SubNodeName, UXMSNode* InNode)
{
	FXMSNodeContainer** ContainerPtrPtr = SubNodes.Find(SubNodeName);
	if (!ContainerPtrPtr) return;

	(*ContainerPtrPtr)->SetGeneric(InNode);
}
