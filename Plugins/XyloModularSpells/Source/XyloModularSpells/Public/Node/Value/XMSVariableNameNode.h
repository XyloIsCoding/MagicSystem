// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSStringValueInterface.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "XMSVariableNameNode.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FXMSVariableNameChangedSignature, const FString& /* New */ , const FString& /* Old */ )

/**
 * Call SetType from the parent node!!!
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
protected:
	virtual void OnParentSet() override;
	
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
	FXMSVariableNameChangedSignature VariableNameChangedDelegate;
	virtual void OnDeclaredVariablesListChanged(const FString& NewVariableName, int32 NewVariableType, const FString& OldVariableName, int32 OldVariableType);
	virtual void SelectByIndex(int32 InStringIndex);
	/** Set the type of variables that can be used by this node */
	virtual void SetType(int32 InVariableType);
	virtual void GetOptions(TArray<FString>& OutStringOptions) const;
protected:
	virtual void CacheString(int32 Index);

private:
	UPROPERTY()
	int32 VariableType = 0;
	UPROPERTY()
	FString CachedName = FString();
};
