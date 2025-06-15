// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "XMSNode.generated.h"

struct FXMSNodeQueryResult;
struct FXMSNodePath;
struct FXMSMultiNodeContainer;
struct FXMSNodeContainer;

/**
 * 
 */
UCLASS(Abstract)
class XYLOMODULARSPELLS_API UXMSNode : public UObject
{
	GENERATED_BODY()
	
public:
	UXMSNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual UXMSNode* GetSubNode(const FXMSNodePath& Path, const FName& Identifier);
	virtual void GetAllSubNodes(const FXMSNodePath& Path, FXMSNodeQueryResult& OutNodes);
	virtual void GetAllSubNodesRecursive(const FXMSNodePath& Path, FXMSNodeQueryResult& OutNodes);
	virtual void SetSubNode(const FXMSNodePath& Path, const FName& Identifier, UXMSNode* InNode);
};
