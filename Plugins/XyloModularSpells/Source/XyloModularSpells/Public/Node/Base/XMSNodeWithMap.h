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

/*--------------------------------------------------------------------------------------------------------------------*/
	// Serialization
	
public:
	virtual TSharedPtr<FJsonObject> SerializeToJson(bool& bOutSuccess) override;
	virtual void DeserializeFromJson(TSharedPtr<FJsonObject>) override;

	// ~Serialization
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// SubNodes
	
	virtual UXMSNode* GetSubNode(const FXMSNodePathElement& PathElement) const override;
	virtual void GetAllSubNodes(FXMSNodeQueryResult& OutNodes) const override;
	virtual void GetAllSubNodes(TArray<UXMSNode*>& OutNodes) const override;
	virtual void SetSubNode(const FXMSNodePathElement& PathElement, UXMSNode* InNode) override;

	virtual void GetSubNodeClassOptions(const FXMSNodePathElement& PathElement, TArray<UClass*>& OutClassOptions) override;
	virtual void GetSubNodesIdentifiers(TArray<FName>& OutIdentifiers) const override;

	// ~SubNodes
/*--------------------------------------------------------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeWithMap
	 */

/*--------------------------------------------------------------------------------------------------------------------*/
	// SubNodes

public:
	virtual UXMSNode* GetSubNode(FName Identifier) const;
	virtual void SetSubNode(FName Identifier, UXMSNode* InNode);
protected:
	/** @remark Spell Editor Only */
	virtual void OnSubNodeChanged(FName Identifier);
private:
	/** Map containing sub-nodes owned by this node. Is automatically updated when a sub-node is initialized */
	TMap<FName, FXMSNodeContainer*> SubNodes;
	
	// ~SubNodes
/*--------------------------------------------------------------------------------------------------------------------*/
	
};

