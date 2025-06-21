// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSTypes.generated.h"

class UXMSNode;

USTRUCT()
struct FXMSNodePathElement
{
	GENERATED_BODY()

	FXMSNodePathElement()
	{
		
	}
	
	FXMSNodePathElement(FName InIdentifier, int32 InIndex = INDEX_NONE)
		: Identifier(InIdentifier)
		, Index(InIndex)
	{
	}

	bool operator==(const FXMSNodePathElement& Other) const
	{
		return Equals(Other);
	}

	bool operator!=(const FXMSNodePathElement& Other) const
	{
		return !Equals(Other);
	}

	bool Equals(const FXMSNodePathElement& Other) const
	{
		return Identifier.IsEqual(Other.Identifier) && Index == Other.Index;
	}

	// TODO: check that this actually works in maps!
	friend FORCEINLINE uint32 GetTypeHash(const FXMSNodePathElement& This)
	{
		return HashCombine(FCrc::MemCrc32(&This.Identifier, sizeof(This.Identifier)), FCrc::MemCrc32(&This.Index, sizeof(This.Index)));
	}

	UPROPERTY()
	FName Identifier = NAME_None;
	UPROPERTY()
	int32 Index = INDEX_NONE;
};

USTRUCT()
struct FXMSNodePath
{
	GENERATED_BODY()

	void ExtendPath(const FXMSNodePathElement& PathElement);
	FString ToString() const;
	bool GetPathElement(int32 Index, FXMSNodePathElement& OutPathElement);
private:
	UPROPERTY()
	TArray<FXMSNodePathElement> Path;
};

USTRUCT()
struct FXMSNodeQueryResult
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TMap<FXMSNodePathElement, UXMSNode*> Nodes;
};


namespace XMSVariableType
{
	UENUM()
	enum EXMSVariableType
	{
		EVT_Integer,
		EVT_Float,
		EVT_Vector,
		EVT_Rotator,
		EVT_String,
		EVT_Object
	};
}

