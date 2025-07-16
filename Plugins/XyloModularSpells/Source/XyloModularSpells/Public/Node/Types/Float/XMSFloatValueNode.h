// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSFloatValueInterface.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "XMSFloatValueNode.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FXMSFloatValueChangedSignature, float /* New */ , float /* Old */ )

/**
 * Contains a raw Float value.
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSFloatValueNode : public UXMSNodeWithValue, public IXMSFloatValueInterface
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
	 * IXMSFloatValueInterface Interface
	 */
	
public:
	virtual bool GetFloat(float& OutFloat) override;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSFloatValueNode
	 */

public:
	FXMSFloatValueChangedSignature FloatValueChangedDelegate;
	virtual void SetFloat(float InFloat);
	virtual float GetFloatUnsafe() const { return Float; }
private:
	float Float = 0.f;
};
