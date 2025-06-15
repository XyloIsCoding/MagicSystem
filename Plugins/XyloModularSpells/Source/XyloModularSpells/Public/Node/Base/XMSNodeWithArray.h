// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNode.h"
#include "XMSNodeWithArray.generated.h"

/**
 * Use a single TXMSMultiNodeContainer to add sub-nodes.
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeWithArray : public UXMSNode
{
	GENERATED_BODY()
	
	friend FXMSMultiNodeContainer;

public:
	virtual UXMSNode* GetSubNode(const FXMSNodePath& Path, const FName& Identifier) override;
	virtual void GetAllSubNodes(const FXMSNodePath& Path, FXMSNodeQueryResult& OutNodes) override;
	virtual void SetSubNode(const FXMSNodePath& Path, const FName& Identifier, UXMSNode* InNode) override;

public:
	virtual UXMSNode* GetSubNode(int32 Index);
	virtual void SetSubNode(int32 Index, UXMSNode* InNode);
	virtual void AddSubNode(UXMSNode* InNode);
	virtual void InsertSubNode(int32 Index, UXMSNode* InNode);
	virtual void RemoveSubNode(int32 Index);
private:
	/** contains array of sub-nodes owned by this node. Is automatically updated when a sub-node is initialized */
	TPair<FName, FXMSMultiNodeContainer*> SubNodes;
};
