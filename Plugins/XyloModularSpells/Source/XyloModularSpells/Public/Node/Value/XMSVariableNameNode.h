// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSStringValueInterface.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "XMSVariableNameNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSVariableNameNode : public UXMSNodeWithValue, public IXMSStringValueInterface
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNode Interface
	 */

public:
	virtual TSharedPtr<FJsonObject> SerializeToJson(bool& bOutSuccess) override;
	virtual void DeserializeFromJson(TSharedPtr<FJsonObject>) override;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSStringValueInterface Interface
	 */

public:
	virtual bool GetString(FString& OutString) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSStringValueNode
	 */
	
public:
	virtual void SetStringIndex(int32 InStringIndex);
	virtual void SetType(int32 InVariableType);
	virtual void GetOptions(TArray<FString>& OutStringOptions) const;
protected:
	virtual void CacheString();

private:
	UPROPERTY()
	int32 StringIndex = 0;
	UPROPERTY()
	int32 VariableType = 0;
	UPROPERTY()
	FString CachedString = FString();
};
