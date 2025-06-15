// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNode.h"
#include "XMSNodeWithMap.generated.h"

/**
 * Use a TXMSNodeContainer for each sub-node.
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeWithMap : public UXMSNode
{
	GENERATED_BODY()

	friend FXMSNodeContainer;

public:
	virtual UXMSNode* GetSubNode(const FXMSNodePath& Path, const FName& Identifier) override;
	virtual void GetAllSubNodes(const FXMSNodePath& Path, FXMSNodeQueryResult& OutNodes) override;
	virtual void SetSubNode(const FXMSNodePath& Path, const FName& Identifier, UXMSNode* InNode) override;
	
public:
	virtual UXMSNode* GetSubNode(const FName& Identifier);
	virtual void SetSubNode(const FName& Identifier, UXMSNode* InNode);
private:
	/** Map containing sub-nodes owned by this node. Is automatically updated when a sub-node is initialized */
	TMap<FName, FXMSNodeContainer*> SubNodes;
};
