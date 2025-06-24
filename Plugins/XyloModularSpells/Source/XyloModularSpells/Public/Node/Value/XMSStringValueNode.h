// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSStringValueInterface.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "XMSStringValueNode.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FXMSStringValueChangedSignature, const FString& /* New */ , const FString& /* Old */ )

/**
 * Contains a raw string value.
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSStringValueNode : public UXMSNodeWithValue, public IXMSStringValueInterface
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
	FXMSStringValueChangedSignature StringValueChangedDelegate;
	virtual void SetString(const FString& InString);
private:
	UPROPERTY()
	FString String = FString();
};
