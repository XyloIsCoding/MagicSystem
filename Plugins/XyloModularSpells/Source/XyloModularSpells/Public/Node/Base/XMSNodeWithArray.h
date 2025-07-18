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

	virtual void GetSubNodeClassOptions(const FXMSNodePathElement& PathElement, TArray<TSubclassOf<UXMSNode>>& OutClassOptions) override;
	virtual void GetSubNodesIdentifiers(TArray<FName>& OutIdentifiers) const override;
	virtual UClass* GetSubNodeInterface(FName Identifier) const override;
	virtual UClass* GetSubNodeClass(FName Identifier) const override;

	// ~SubNodes
/*--------------------------------------------------------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeWithArray
	 */

/*--------------------------------------------------------------------------------------------------------------------*/
	// SubNodes
	
public:
	/** @remark Spell Editor Only */
	FXMSSubNodeChangedSignature SubNodeAddedDelegate;
	/** @remark Spell Editor Only */
	FXMSSubNodeChangedSignature SubNodeRemovedDelegate;
	virtual UXMSNode* GetSubNode(int32 Index) const;
	virtual void SetSubNode(int32 Index, UXMSNode* InNode);
	virtual void AddSubNode(UXMSNode* InNode);
	virtual void InsertSubNode(int32 Index, UXMSNode* InNode);
	virtual void RemoveSubNode(int32 Index);

protected:
	/** Called when an existing slot of FXMSMultiNodeContainer is changed
	 * @remark This is called AFTER parent is set on the sub-node.
	 * @remark Spell Editor Only */
	virtual void OnSubNodeChanged(FName Identifier, int32 Index);
	/** Called when a slot of FXMSMultiNodeContainer is added
	 * @remark This is called AFTER parent is set on the sub-node
	 * @remark Spell Editor Only */
	virtual void OnSubNodeAdded(FName Identifier, int32 Index);
	/** Called when a slot of FXMSMultiNodeContainer is removed
	 * @remark This is called AFTER parent is set on the sub-node
	 * @remark Spell Editor Only */
	virtual void OnSubNodeRemoved(FName Identifier, int32 Index);
private:
	/** contains array of sub-nodes owned by this node. Is automatically updated when a sub-node is initialized */
	TPair<FName, FXMSMultiNodeContainer*> SubNodes;

	// ~SubNodes
/*--------------------------------------------------------------------------------------------------------------------*/
	
};
