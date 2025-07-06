// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSVariableTypeValueInterface.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "XMSVariableTypeValueNode.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FXMSVariableTypeChangedSignature, const FGameplayTag& /* New */ , const FGameplayTag& /* Old */ )

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSVariableTypeValueNode : public UXMSNodeWithValue, public IXMSVariableTypeValueInterface
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
	 * IXMSVariableTypeValueInterface Interface
	 */
	
public:
	virtual const FGameplayTag& GetVariableType() override { return VariableType; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSVariableTypeValueNode
	 */

public:
	FXMSVariableTypeChangedSignature VariableTypeChangedDelegate;
	virtual void GetPossibleTypes(TArray<FGameplayTag>& OutTypes);
	virtual void SetVariableType(const FGameplayTag& InType);
private:
	FGameplayTag VariableType = XMSVariableType::None;
};
