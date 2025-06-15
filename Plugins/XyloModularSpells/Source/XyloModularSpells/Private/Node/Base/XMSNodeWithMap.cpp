// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Base/XMSNodeWithMap.h"

#include "Node/XMSNodeContainer.h"


UXMSNode* UXMSNodeWithMap::GetSubNode(const FName& SubNodeName)
{
	FXMSNodeContainer** ContainerPtrPtr = SubNodes.Find(SubNodeName);
	if (!ContainerPtrPtr) return nullptr;

	return (*ContainerPtrPtr)->GetGeneric();
}

void UXMSNodeWithMap::SetSubNode(const FName& SubNodeName, UXMSNode* InNode)
{
	FXMSNodeContainer** ContainerPtrPtr = SubNodes.Find(SubNodeName);
	if (!ContainerPtrPtr) return;

	(*ContainerPtrPtr)->SetGeneric(InNode);
}