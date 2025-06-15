// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNode.h"
#include "XMSNodeWithArray.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeWithArray : public UXMSNode
{
	GENERATED_BODY()
	
	friend FXMSMultiNodeContainer;

public:
	virtual UXMSNode* GetSubNode(int32 Index);
	virtual void SetSubNode(int32 Index, UXMSNode* InNode);
	virtual void AddSubNode(UXMSNode* InNode);
	virtual void InsertSubNode(int32 Index, UXMSNode* InNode);
	virtual void RemoveSubNode(int32 Index);
private:
	TPair<FString, FXMSMultiNodeContainer*> SubNodes;
};
