// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "XMSNode.generated.h"

struct FXMSNodeContainer;

/**
 * Use TXMSNodeContainer to add a sub-node.
 * It is preferable to make sub-nodes private, and access them through GetSubNode and SetSubNode
 */
UCLASS(Abstract)
class XYLOMODULARSPELLS_API UXMSNode : public UObject
{
	GENERATED_BODY()

	friend FXMSNodeContainer;
	
public:
	UXMSNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual UXMSNode* GetSubNode(const FString& SubNodeName);
	virtual void SetSubNode(const FString& SubNodeName, UXMSNode* InNode);
private:
	/** Map containing subnodes owned by this node. Is automatically updated when a subnode is initialized */
	TMap<FString, FXMSNodeContainer*> SubNodes;
};
