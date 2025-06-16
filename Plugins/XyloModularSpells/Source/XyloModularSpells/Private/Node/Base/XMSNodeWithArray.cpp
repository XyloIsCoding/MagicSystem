// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Base/XMSNodeWithArray.h"

#include "XMSTypes.h"
#include "Node/XMSNodeContainer.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

UXMSNode* UXMSNodeWithArray::GetSubNode(const FXMSNodePathElement& PathElement)
{
	if (PathElement.Identifier != SubNodes.Key) return nullptr;
	return GetSubNode(PathElement.Index);
}

void UXMSNodeWithArray::GetAllSubNodes(FXMSNodeQueryResult& OutNodes)
{
	if (!SubNodes.Value)
	{
		UE_LOG(LogTemp, Error, TEXT("UXMSNodeWithArray::GetAllSubNodes >> Sub-node container ptr not found for [%s]"), *SubNodes.Key.ToString())
		return;
	}
	for (auto It = SubNodes.Value->GetAllGeneric().CreateIterator(); It; ++It)
	{
		OutNodes.Nodes.Emplace(FXMSNodePathElement(SubNodes.Key, It.GetIndex()), *It);
	}
}

void UXMSNodeWithArray::SetSubNode(const FXMSNodePathElement& PathElement, UXMSNode* InNode)
{
	if (PathElement.Identifier != SubNodes.Key) return;
	SetSubNode(PathElement.Index, InNode);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeWithArray
 */

UXMSNode* UXMSNodeWithArray::GetSubNode(int32 Index)
{
	FXMSMultiNodeContainer* ContainerPtr = SubNodes.Value;
	if (!ContainerPtr) return nullptr;

	return ContainerPtr->GetGeneric(Index);
}

void UXMSNodeWithArray::SetSubNode(int32 Index, UXMSNode* InNode)
{
	FXMSMultiNodeContainer* ContainerPtr = SubNodes.Value;
	if (!ContainerPtr) return;

	ContainerPtr->SetGeneric(Index, InNode);
}

void UXMSNodeWithArray::AddSubNode(UXMSNode* InNode)
{
	FXMSMultiNodeContainer* ContainerPtr = SubNodes.Value;
	if (!ContainerPtr) return;

	ContainerPtr->AddGeneric(InNode);
}

void UXMSNodeWithArray::InsertSubNode(int32 Index, UXMSNode* InNode)
{
	FXMSMultiNodeContainer* ContainerPtr = SubNodes.Value;
	if (!ContainerPtr) return;

	ContainerPtr->InsertGeneric(Index, InNode);
}

void UXMSNodeWithArray::RemoveSubNode(int32 Index)
{
	FXMSMultiNodeContainer* ContainerPtr = SubNodes.Value;
	if (!ContainerPtr) return;

	ContainerPtr->Remove(Index);
}
