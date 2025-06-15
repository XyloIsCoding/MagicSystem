// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Base/XMSNodeWithMap.h"

#include "XMSTypes.h"
#include "Node/XMSNodeContainer.h"


UXMSNode* UXMSNodeWithMap::GetSubNode(const FXMSNodePath& Path, const FName& Identifier)
{
	
}

void UXMSNodeWithMap::GetAllSubNodes(const FXMSNodePath& Path, FXMSNodeQueryResult& OutNodes)
{

	
	for (TPair<FName, FXMSNodeContainer*>& SubNode : SubNodes)
	{
		OutNodes.Nodes.Append({ /* Path + SubNode.Key */, SubNode.Value });
	}
}

void UXMSNodeWithMap::SetSubNode(const FXMSNodePath& Path, const FName& Identifier, UXMSNode* InNode)
{
	
}

UXMSNode* UXMSNodeWithMap::GetSubNode(const FName& Identifier)
{
	FXMSNodeContainer** ContainerPtrPtr = SubNodes.Find(Identifier);
	if (!ContainerPtrPtr) return nullptr;

	return (*ContainerPtrPtr)->GetGeneric();
}

void UXMSNodeWithMap::SetSubNode(const FName& Identifier, UXMSNode* InNode)
{
	FXMSNodeContainer** ContainerPtrPtr = SubNodes.Find(Identifier);
	if (!ContainerPtrPtr) return;

	(*ContainerPtrPtr)->SetGeneric(InNode);
}