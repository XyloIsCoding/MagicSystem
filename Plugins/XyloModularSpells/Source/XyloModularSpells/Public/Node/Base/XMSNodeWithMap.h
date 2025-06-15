// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNode.h"
#include "XMSNodeWithMap.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeWithMap : public UXMSNode
{
	GENERATED_BODY()

	friend FXMSNodeContainer;
	
public:
	virtual UXMSNode* GetSubNode(const FString& SubNodeName);
	virtual void SetSubNode(const FString& SubNodeName, UXMSNode* InNode);
private:
	/** Map containing subnodes owned by this node. Is automatically updated when a subnode is initialized */
	TMap<FString, FXMSNodeContainer*> SubNodes;
};
