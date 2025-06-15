// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Base/XMSNode.h"

#include "Node/XMSNodeContainer.h"

UXMSNode::UXMSNode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

UXMSNode* UXMSNode::GetSubNode(const FXMSNodePath& Path, const FName& Identifier)
{
	return nullptr;
}

void UXMSNode::GetAllSubNodes(const FXMSNodePath& Path, FXMSNodeQueryResult& OutNodes)
{
}

void UXMSNode::GetAllSubNodesRecursive(const FXMSNodePath& Path, FXMSNodeQueryResult& OutNodes)
{
	// Calls GetAllSubNodes on this and calls it again on all found results
}

void UXMSNode::SetSubNode(const FXMSNodePath& Path, const FName& Identifier, UXMSNode* InNode)
{
}

