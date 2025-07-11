// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/Types/String/XMSStringValueInterface.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "XMSVariableNameValueNode.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FXMSVariableNameChangedSignature, const FString& /* New */ , const FString& /* Old */, bool /* bValidName */)

USTRUCT()
struct FXMSCachedVariableName
{
	GENERATED_BODY()

public:
	const FString& GetName() const { return CachedName; }
	bool IsValidName() const { return bValidName; }
	bool GetValidName(FString& OutName);

	void SetName(const FString& InName);
	void InvalidateName();
	
protected:
	UPROPERTY()
	FString CachedName;
	UPROPERTY()
	bool bValidName = true;
};


/**
 * Call SetType from the parent node!!!
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSVariableNameValueNode : public UXMSNodeWithValue, public IXMSStringValueInterface
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
	/** @remark Only bound if in spell editor */
	virtual void OnDeclaredVariablesListChanged(const FString& NewVariableName, const FGameplayTag& NewVariableType, const FString& OldVariableName, const FGameplayTag& OldVariableType);
	/** Set the type of variables that can be used by this node. Usually only called by parent node */
	virtual void SetType(const FGameplayTag& InVariableType);

public:
	virtual void GetOptions(TArray<FString>& OutStringOptions) const;
	
public:
	FXMSVariableNameChangedSignature VariableNameChangedDelegate;
	void BroadcastVariableNameChangedDelegate(const FString& OldName = FString());
	virtual bool GetLastValidName(FString& OutName);
	virtual void SetName(const FString& InName);
protected:
	virtual void InvalidateName();

private:
	/** Non serialized. It is set by parent node */
	UPROPERTY()
	FGameplayTag VariableType = XMSValueType::None;
	UPROPERTY()
	FXMSCachedVariableName CachedVariableName;
};
