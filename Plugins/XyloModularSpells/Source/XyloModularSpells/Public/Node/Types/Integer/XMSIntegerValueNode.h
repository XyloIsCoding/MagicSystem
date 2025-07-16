// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSIntegerValueInterface.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "XMSIntegerValueNode.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FXMSIntegerValueChangedSignature, int32 /* New */ , int32 /* Old */ )

/**
 * Contains a raw integer value.
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSIntegerValueNode : public UXMSNodeWithValue, public IXMSIntegerValueInterface
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
	 * IXMSIntegerValueInterface Interface
	 */
	
public:
	virtual bool GetInteger(int32& OutInteger) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSIntegerValueNode
	 */

public:
	FXMSIntegerValueChangedSignature IntegerValueChangedDelegate;
	virtual void SetInteger(int32 InInteger);
	virtual int32 GetIntegerUnsafe() const { return Integer; }
private:
	int32 Integer = 0;
};
