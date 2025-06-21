// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "XMSNode.generated.h"

struct FXMSNodeQueryResult;
struct FXMSNodePathElement;

/**
 * 
 */
UCLASS(Abstract)
class XYLOMODULARSPELLS_API UXMSNode : public UObject
{
	GENERATED_BODY()
	
public:
	UXMSNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNode
	 */
	
public:
	/** Serialize this node and all its sub-nodes to Json recursively */
	virtual TSharedPtr<FJsonObject> SerializeToJson(bool& bOutSuccess);
	/** Init this node from a Json object, also instantiating all sub-nodes recursively using the passed in outer */
	virtual void DeserializeFromJson(TSharedPtr<FJsonObject>);
	
	virtual UXMSNode* GetSubNode(const FXMSNodePathElement& PathElement) { return nullptr; }
	virtual void GetAllSubNodes(FXMSNodeQueryResult& OutNodes) {}
	virtual void SetSubNode(const FXMSNodePathElement& PathElement, UXMSNode* InNode) {}

	virtual void GetNodesIdentifiers(TArray<FName>& OutIdentifiers) const {}
	
protected:
	static const FString NodeClassJsonKey;
};
