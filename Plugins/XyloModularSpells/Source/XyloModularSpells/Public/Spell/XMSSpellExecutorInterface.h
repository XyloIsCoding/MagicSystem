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
	virtual void SetIntegerValue(FString Name, int32 Value) = 0;
	virtual bool GetIntegerValue(FString Name, int32& OutValue) = 0;
	virtual void GetAllIntegerValueNames(TArray<FString>& OutNames) = 0;
	
	virtual void SetFlotValue(FString Name, float Value) = 0;
	virtual bool GetFlotValue(FString Name, float& OutValue) = 0;
	virtual void GetAllFloatValueNames(TArray<FString>& OutNames) = 0;
	
	virtual void SetVectorValue(FString Name, FVector Value) = 0;
	virtual bool GetVectorValue(FString Name, FVector& OutValue) = 0;
	virtual void GetAllVectorValueNames(TArray<FString>& OutNames) = 0;
	
	virtual void SetRotatorValue(FString Name, FRotator Value) = 0;
	virtual bool GetRotatorValue(FString Name, FRotator& OutValue) = 0;
	virtual void GetAllRotatorValueNames(TArray<FString>& OutNames) = 0;
	
	virtual void SetStringValue(FString Name, FString Value) = 0;
	virtual bool GetStringValue(FString Name, FString& OutValue) = 0;
	virtual void GetAllStringValueNames(TArray<FString>& OutNames) = 0;

	virtual void SetObjectValue(FString Name, UObject* Value) = 0;
	virtual bool GetObjectValue(FString Name, UObject*& OutValue) = 0;
	virtual void GetAllObjectValueNames(TArray<FString>& OutNames) = 0;
};
