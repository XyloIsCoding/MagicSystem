// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "XMSTypes.h"
#include "UObject/Object.h"
#include "XMSNode.generated.h"

struct FXMSNodeContainer;
struct FXMSMultiNodeContainer;
struct FXMSNodeQueryResult;
struct FXMSNodePathElement;

DECLARE_MULTICAST_DELEGATE(FXMSRemovedFromParentSignature)
DECLARE_MULTICAST_DELEGATE_OneParam(FXMSSubNodeChangedSignature, const FXMSNodePathElement&)
DECLARE_MULTICAST_DELEGATE_OneParam(FXMSPathIndexChangedSignature, int32)

/**
 * 
 */
UCLASS(Abstract)
class XYLOMODULARSPELLS_API UXMSNode : public UObject
{
	GENERATED_BODY()

	friend FXMSMultiNodeContainer;
	friend FXMSNodeContainer;
	
public:
	UXMSNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UObject
	 */

public:
	virtual void BeginDestroy() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNode
	 */
	
public:
	bool IsInSpellEditorContext() const;

public:
	/** Fills OutFlags with flags defining special behaviour for this node
	 * <p> An example would be loop nodes, which allow "break" or "continue" to be used inside their scope */
	virtual void GetNodeFlags(FGameplayTagContainer& OutFlags) const {}
	/** Calls GetNodeFlags on all nodes higher in hierarchy */
	void GetNodeFlagsRecursive(FGameplayTagContainer& OutFlags) const;

/*--------------------------------------------------------------------------------------------------------------------*/
	// Serialization

public:
	static const FString NodeClassJsonKey;
	/** Serialize this node and all its sub-nodes to Json recursively */
	virtual TSharedPtr<FJsonObject> SerializeToJson(bool& bOutSuccess);
	/** Init this node from a Json object, also instantiating all sub-nodes recursively using the passed in outer */
	virtual void DeserializeFromJson(TSharedPtr<FJsonObject>);

	// ~Serialization
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// SubNodes

	/** @remark Spell Editor Only */
	FXMSSubNodeChangedSignature SubNodeChangedDelegate;
	virtual UXMSNode* GetSubNode(const FXMSNodePathElement& PathElement) const { return nullptr; }
	virtual void GetAllSubNodes(FXMSNodeQueryResult& OutNodes) const {}
	virtual void GetAllSubNodes(TArray<UXMSNode*>& OutNodes) const {}
	virtual void SetSubNode(const FXMSNodePathElement& PathElement, UXMSNode* InNode) {}

	virtual void GetSubNodeClassOptions(const FXMSNodePathElement& PathElement, TArray<TSubclassOf<UXMSNode>>& OutClassOptions) {}
	/** @return: the Identifiers of all sub-nodes */
	virtual void GetSubNodesIdentifiers(TArray<FName>& OutIdentifiers) const {}
	virtual UClass* GetSubNodeInterface(FName Identifier) const { return nullptr; }
	virtual UClass* GetSubNodeClass(FName Identifier) const { return nullptr; }

	// ~SubNodes
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// Hierarchy
	
public:
	/** Gets all the parent nodes of this node
	 * @param OutHierarchy: Ordered array with all the parents hierarchy of this node, ordered from the closest
	 *						relative to the further one (parent, grandparent, grand grandparent, ...) */
	void GetHierarchy(TArray<UXMSNode*>& OutHierarchy) const;
	/** Checks if this node is in the sub-nodes chain of Other or of a node that comes after Other inside
	 * the same NodeWithArray that owns Other */
	bool IsInScopeOf(UXMSNode* Other) const;
	bool IsInScopeOf(UXMSNode* Other, const TArray<UXMSNode*>& ThisNodeHierarchy) const;

	// ~Hierarchy
/*--------------------------------------------------------------------------------------------------------------------*/
	
/*--------------------------------------------------------------------------------------------------------------------*/
	// ParentNode
	
public:
	/** @remark Spell Editor Only */
	FXMSPathIndexChangedSignature PathIndexChangedDelegate; 
	FXMSRemovedFromParentSignature RemovedFromParentDelegate;
	UXMSNode* GetParentNode() const { return ParentNode.Get(); }
	const FXMSNodePathElement& GetPathFromParentNode() const { return PathFromParentNode; }
protected:
	/** Called when this node is set in a container */
	virtual void OnParentSet() {}
	/** Called before the parent data of this node is deleted */
	virtual void PreRemovedFromParent() {}
	/** Called after the parent data of this node is deleted */
	virtual void PostRemovedFromParent() {}
private:
	void RemoveFromParent();
	/**  Called exclusively by node containers after setting reference to this node */
	void ReparentNode(UXMSNode* InParentNode, const FXMSNodePathElement& InPathFromParent);
	/**  Called exclusively by node containers after removing reference to this node */
	void RemovedFromParent_Internal();

protected:
	/** Fixed for the lifetime of the node */
	UPROPERTY()
	TWeakObjectPtr<UXMSNode> ParentNode;
	/** While identifier is fixed for the lifetime of the node, index might change if owned by a NodeWithArray */
	UPROPERTY()
	FXMSNodePathElement PathFromParentNode;
	
	// ~ParentNode
/*--------------------------------------------------------------------------------------------------------------------*/
	
};
