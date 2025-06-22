// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSSpellExecutorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSSpellExecutorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSSpellExecutorInterface
{
	GENERATED_BODY()

public:
	virtual void SetIntegerValue(const FString& Name, int32 Value) = 0;
	virtual bool GetIntegerValue(const FString& Name, int32& OutValue) = 0;
	virtual void GetAllIntegerValueNames(TArray<FString>& OutNames) = 0;
	
	virtual void SetFlotValue(const FString& Name, float Value) = 0;
	virtual bool GetFlotValue(const FString& Name, float& OutValue) = 0;
	virtual void GetAllFloatValueNames(TArray<FString>& OutNames) = 0;
	
	virtual void SetVectorValue(const FString& Name, FVector Value) = 0;
	virtual bool GetVectorValue(const FString& Name, FVector& OutValue) = 0;
	virtual void GetAllVectorValueNames(TArray<FString>& OutNames) = 0;
	
	virtual void SetRotatorValue(const FString& Name, FRotator Value) = 0;
	virtual bool GetRotatorValue(const FString& Name, FRotator& OutValue) = 0;
	virtual void GetAllRotatorValueNames(TArray<FString>& OutNames) = 0;
	
	virtual void SetStringValue(const FString& Name, FString Value) = 0;
	virtual bool GetStringValue(const FString& Name, FString& OutValue) = 0;
	virtual void GetAllStringValueNames(TArray<FString>& OutNames) = 0;

	virtual void SetObjectValue(const FString& Name, UObject* Value) = 0;
	virtual bool GetObjectValue(const FString& Name, UObject*& OutValue) = 0;
	virtual void GetAllObjectValueNames(TArray<FString>& OutNames) = 0;
};
