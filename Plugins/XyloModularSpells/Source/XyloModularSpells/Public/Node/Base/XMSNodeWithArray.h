// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNode.h"
#include "XMSNodeWithArray.generated.h"

struct FXMSMultiNodeContainer;

/**
 * Use a single TXMSMultiNodeContainer to add sub-nodes.
 */
UCLASS(Abstract)
class XYLOMODULARSPELLS_API UXMSNodeWithArray : public UXMSNode
{
	GENERATED_BODY()
	
	friend FXMSMultiNodeContainer;

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeWithArray
	 */
	
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
