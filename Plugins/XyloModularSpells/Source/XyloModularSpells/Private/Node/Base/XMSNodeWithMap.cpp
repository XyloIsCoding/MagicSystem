// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Base/XMSNodeWithMap.h"

#include "XMSTypes.h"
#include "Node/XMSNodeContainer.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

UXMSNode* UXMSNodeWithMap::GetSubNode(const FXMSNodePathElement& PathElement)
{
	return GetSubNode(PathElement.Identifier);
}

void UXMSNodeWithMap::GetAllSubNodes(FXMSNodeQueryResult& OutNodes)
{
	for (TPair<FName, FXMSNodeContainer*>& SubNode : SubNodes)
	{
		if (!SubNode.Value)
		{
			UE_LOG(LogTemp, Error, TEXT("UXMSNodeWithMap::GetAllSubNodes >> Sub-node container ptr not found for [%s]"), *SubNode.Key.ToString())
			continue;
		}
		OutNodes.Nodes.Emplace(FXMSNodePathElement(SubNode.Key), SubNode.Value->GetGeneric());
	}
}

void UXMSNodeWithMap::SetSubNode(const FXMSNodePathElement& PathElement, UXMSNode* InNode)
{
	SetSubNode(PathElement.Identifier, InNode);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWithMap
 */

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