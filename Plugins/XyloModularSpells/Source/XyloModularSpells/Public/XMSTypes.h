// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSTypes.generated.h"


class XMSNode;

USTRUCT()
struct FXMSNodePathElement
{
	GENERATED_BODY()

	FXMSNodePathElement(FName InIdentifier, int32 InIndex = INDEX_NONE)
		: Identifier(InIdentifier)
		, Index(InIndex)
	{
	}

	FName Identifier = NAME_None;
	int32 Index = INDEX_NONE;
};

USTRUCT()
struct FXMSNodePath
{
	GENERATED_BODY()

	void ExtendPath(const FXMSNodePathElement& PathElement);
	FString ToString() const;
private:
	TArray<FXMSNodePathElement> Path;
};

USTRUCT()
struct FXMSNodeQueryResult
{
	GENERATED_BODY()

public:
	TMap<FXMSNodePathElement, XMSNode*> Nodes;
};
