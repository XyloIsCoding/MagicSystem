// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeInterface.h"
#include "UObject/Object.h"
#include "XMSNode.generated.h"

struct FXMSNodeContainer;

/**
 * Use TXMSNodeContainer to add a sub-node.
 * It is preferable to make sub-nodes private, and access them through IXMSNodeInterface
 */
UCLASS(Abstract)
class XYLOMODULARSPELLS_API UXMSNode : public UObject, public IXMSNodeInterface
{
	GENERATED_BODY()

	friend FXMSNodeContainer;
	
public:
	UXMSNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual UXMSNode* GetSubNode(const FString& SubNodeName) override;
	virtual void SetSubNode(const FString& SubNodeName, UXMSNode* InNode) override;
private:
	/** Map containing subnodes owned by this node. Is automatically updated when a subnode is initialized */
	TMap<FString, FXMSNodeContainer*> SubNodes;
};
