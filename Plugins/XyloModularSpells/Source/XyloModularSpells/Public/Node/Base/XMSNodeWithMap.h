// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNode.h"
#include "XMSNodeWithMap.generated.h"

struct FXMSNodeContainer;

/**
 * Use a TXMSNodeContainer for each sub-node.
 */
UCLASS(Abstract)
class XYLOMODULARSPELLS_API UXMSNodeWithMap : public UXMSNode
{
	GENERATED_BODY()

	friend FXMSNodeContainer;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNode Interface
	 */
	
public:
	virtual TSharedPtr<FJsonObject> SerializeToJson(bool& bOutSuccess) override;
	virtual void DeserializeFromJson(TSharedPtr<FJsonObject>) override;
	
	virtual UXMSNode* GetSubNode(const FXMSNodePathElement& PathElement) override;
	virtual void GetAllSubNodes(FXMSNodeQueryResult& OutNodes) override;
	virtual void SetSubNode(const FXMSNodePathElement& PathElement, UXMSNode* InNode) override;

	virtual void GetNodesIdentifiers(TArray<FName>& OutIdentifiers) const override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeWithMap
	 */
	
public:
	virtual UXMSNode* GetSubNode(const FName& Identifier);
	virtual void SetSubNode(const FName& Identifier, UXMSNode* InNode);
private:
	/** Map containing sub-nodes owned by this node. Is automatically updated when a sub-node is initialized */
	TMap<FName, FXMSNodeContainer*> SubNodes;
};
