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
	virtual UXMSNode* GetSubNode(const FName& SubNodeName);
	virtual void SetSubNode(const FName& SubNodeName, UXMSNode* InNode);
private:
	/** Map containing sub-nodes owned by this node. Is automatically updated when a sub-node is initialized */
	TMap<FName, FXMSNodeContainer*> SubNodes;
};
