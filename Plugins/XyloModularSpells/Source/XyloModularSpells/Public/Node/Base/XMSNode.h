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
	virtual UXMSNode* GetSubNode(const FXMSNodePathElement& PathElement) { return nullptr; }
	virtual void GetAllSubNodes(FXMSNodeQueryResult& OutNodes) {}
	virtual void SetSubNode(const FXMSNodePathElement& PathElement, UXMSNode* InNode) {}
};
