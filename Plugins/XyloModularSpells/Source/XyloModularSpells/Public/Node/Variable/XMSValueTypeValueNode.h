// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSValueTypeValueInterface.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "XMSValueTypeValueNode.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FXMSValueTypeChangedSignature, const FGameplayTag& /* New */ , const FGameplayTag& /* Old */ )

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSValueTypeValueNode : public UXMSNodeWithValue, public IXMSValueTypeValueInterface
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
	 * IXMSValueTypeValueInterface Interface
	 */
	
public:
	virtual const FGameplayTag& GetValueType() override { return ValueType; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSValueTypeValueNode
	 */

public:
	FXMSValueTypeChangedSignature ValueTypeChangedDelegate;
	virtual void GetPossibleTypes(TArray<FGameplayTag>& OutTypes);
	virtual void SetValueType(const FGameplayTag& InType);
private:
	FGameplayTag ValueType = XMSValueType::None;
};
