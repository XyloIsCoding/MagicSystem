// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSRotatorValueInterface.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "XMSRotatorValueNode.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FXMSRotatorValueChangedSignature, FRotator /* New */ , FRotator /* Old */ )

/**
 * Contains a raw Rotator value.
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSRotatorValueNode : public UXMSNodeWithValue, public IXMSRotatorValueInterface
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
	 * IXMSRotatorValueInterface Interface
	 */
	
public:
	virtual bool GetRotator(FRotator& OutRotator) override;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSRotatorValueNode
	 */

public:
	FXMSRotatorValueChangedSignature RotatorValueChangedDelegate;
	virtual void SetRotator(FRotator InRotator);
	virtual FRotator GetRotatorUnsafe() const { return Rotator; }
private:
	FRotator Rotator = FRotator::ZeroRotator;
};
