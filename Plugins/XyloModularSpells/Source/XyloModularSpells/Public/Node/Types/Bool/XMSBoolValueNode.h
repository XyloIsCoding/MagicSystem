// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSBoolValueInterface.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "XMSBoolValueNode.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FXMSBoolValueChangedSignature, bool /* New */ , bool /* Old */ )

/**
 * Contains a raw Bool value.
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSBoolValueNode : public UXMSNodeWithValue, public IXMSBoolValueInterface
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
	 * IXMSBoolValueInterface Interface
	 */
	
public:
	virtual bool GetBool(bool& OutBool) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSBoolValueNode
	 */

public:
	FXMSBoolValueChangedSignature BoolValueChangedDelegate;
	virtual void SetBool(bool InBool);
	virtual bool GetBoolUnsafe() const { return Bool; }
private:
	bool Bool = false;
};
