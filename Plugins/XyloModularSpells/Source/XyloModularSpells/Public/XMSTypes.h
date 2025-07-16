// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "XMSTypes.generated.h"

class UXMSNode;

USTRUCT(BlueprintType)
struct FXMSNodePathElement
{
	GENERATED_BODY()

	FXMSNodePathElement()
	{
		
	}
	
	FXMSNodePathElement(FName InIdentifier, int32 InIndex = 0)
		: Identifier(InIdentifier)
		, Index(InIndex)
	{
	}

	bool operator==(const FXMSNodePathElement& Other) const
	{
		return Identifier.IsEqual(Other.Identifier) && Index == Other.Index;
	}

	bool operator!=(const FXMSNodePathElement& Other) const
	{
		return !(*this == Other);
	}

	friend inline uint32 GetTypeHash( const FXMSNodePathElement& Key )
	{
		uint32 Hash = 0;
		Hash = HashCombine(Hash, GetTypeHash(Key.Identifier));
		Hash = HashCombine(Hash, GetTypeHash(Key.Index));
		return Hash;
	}

	void Reset()
	{
		Identifier = NAME_None;
		Index = INDEX_NONE;
	}

	UPROPERTY(BlueprintReadWrite)
	FName Identifier = NAME_None;
	UPROPERTY(BlueprintReadWrite)
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


namespace XMSValueType
{
	XYLOMODULARSPELLS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(None)
	XYLOMODULARSPELLS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Integer)
	XYLOMODULARSPELLS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Float)
	XYLOMODULARSPELLS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Vector)
	XYLOMODULARSPELLS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Rotator)
	XYLOMODULARSPELLS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(String)
	XYLOMODULARSPELLS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Object)
}

namespace XMSNodeFlag
{
	XYLOMODULARSPELLS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Impossible)
	XYLOMODULARSPELLS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Loop)
}
