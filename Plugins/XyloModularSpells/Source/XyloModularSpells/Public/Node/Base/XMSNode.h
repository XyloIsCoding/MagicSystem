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
	
	virtual UXMSNode* GetSubNode(const FXMSNodePathElement& PathElement) { return nullptr; }
	virtual void GetAllSubNodes(FXMSNodeQueryResult& OutNodes) {}
	virtual void SetSubNode(const FXMSNodePathElement& PathElement, UXMSNode* InNode) {}

	/** @return: the Identifiers of all sub-nodes */
	virtual void GetSubNodesIdentifiers(TArray<FName>& OutIdentifiers) const {}
	
	/** Fills OutFlags with flags defining special behaviour for this node
	 * <p> An example would be loop nodes, which allow "break" or "continue" to be used inside their scope */
	virtual void GetNodeFlags(FGameplayTagContainer& OutFlags) const {}
	/** Calls GetNodeFlags on all nodes higher in hierarchy */
	void GetNodeFlagsRecursive(FGameplayTagContainer& OutFlags) const;

protected:
	virtual void OnRemovedFromParent() {}
	
private:
	void ReparentNode(UXMSNode* InParentNode, const FXMSNodePathElement& InPathFromParent);
	
protected:
	static const FString NodeClassJsonKey;
	UPROPERTY()
	TWeakObjectPtr<UXMSNode> ParentNode;
	UPROPERTY()
	FXMSNodePathElement PathFromParent;
};
