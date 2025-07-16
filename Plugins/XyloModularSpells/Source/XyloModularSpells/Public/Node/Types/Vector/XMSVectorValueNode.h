// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSVectorValueInterface.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "XMSVectorValueNode.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FXMSVectorValueChangedSignature, FVector /* New */ , FVector /* Old */ )

/**
 * Contains a raw Vector value.
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSVectorValueNode : public UXMSNodeWithValue, public IXMSVectorValueInterface
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
	 * IXMSVectorValueInterface Interface
	 */
	
public:
	virtual bool GetVector(FVector& OutVector) override;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSVectorValueNode
	 */

public:
	FXMSVectorValueChangedSignature VectorValueChangedDelegate;
	virtual void SetVector(FVector InVector);
	virtual FVector GetVectorUnsafe() const { return Vector; }
private:
	FVector Vector = FVector::ZeroVector;
};
