// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Base/XMSNodeWithArray.h"

#include "Node/XMSNodeContainer.h"

UXMSNode* UXMSNodeWithArray::GetSubNode(const FXMSNodePath& Path, const FName& Identifier)
{
	
}

void UXMSNodeWithArray::GetAllSubNodes(const FXMSNodePath& Path, FXMSNodeQueryResult& OutNodes)
{
	
}

void UXMSNodeWithArray::SetSubNode(const FXMSNodePath& Path, const FName& Identifier, UXMSNode* InNode)
{
	
}

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
