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
	 * UXMSNode
	 */
	
public:
	bool IsInSpellEditorContext() const;
	
	/** Serialize this node and all its sub-nodes to Json recursively */
	virtual TSharedPtr<FJsonObject> SerializeToJson(bool& bOutSuccess);
	/** Init this node from a Json object, also instantiating all sub-nodes recursively using the passed in outer */
	virtual void DeserializeFromJson(TSharedPtr<FJsonObject>);
	
	virtual UXMSNode* GetSubNode(const FXMSNodePathElement& PathElement) const { return nullptr; }
	virtual void GetAllSubNodes(FXMSNodeQueryResult& OutNodes) const {}
	virtual void GetAllSubNodes(TArray<UXMSNode*>& OutNodes) const {}
	virtual void SetSubNode(const FXMSNodePathElement& PathElement, UXMSNode* InNode) {}

	FXMSSubNodeChangedSignature SubNodeChangedDelegate;

public:
	/** @return: the Identifiers of all sub-nodes */
	virtual void GetSubNodesIdentifiers(TArray<FName>& OutIdentifiers) const {}
	
	/** Fills OutFlags with flags defining special behaviour for this node
	 * <p> An example would be loop nodes, which allow "break" or "continue" to be used inside their scope */
	virtual void GetNodeFlags(FGameplayTagContainer& OutFlags) const {}
	/** Calls GetNodeFlags on all nodes higher in hierarchy */
	void GetNodeFlagsRecursive(FGameplayTagContainer& OutFlags) const;

public:
	/**
	 * @param OutHierarchy: Ordered array with all the parents hierarchy of this node, ordered from the closest
	 *						relative to the further one (parent, grandparent, grand grandparent, ...)
	 */
	void GetHierarchy(TArray<UXMSNode*>& OutHierarchy) const;
	bool IsInScopeOf(UXMSNode* Other) const;
	bool IsInScopeOf(UXMSNode* Other, const TArray<UXMSNode*>& ThisNodeHierarchy) const;

public:
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
	void ReparentNode(UXMSNode* InParentNode, const FXMSNodePathElement& InPathFromParent);
	void RemoveFromParent();
	
protected:
	static const FString NodeClassJsonKey;
	UPROPERTY()
	TWeakObjectPtr<UXMSNode> ParentNode;
	UPROPERTY()
	FXMSNodePathElement PathFromParentNode;
};
