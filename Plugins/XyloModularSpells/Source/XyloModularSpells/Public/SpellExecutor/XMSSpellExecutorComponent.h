// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XMSSpellExecutorComponent.generated.h"


struct FGameplayTag;

USTRUCT(BlueprintType)
struct FXMSSpellBrain
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, int32> IntegerVariables;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, float> FloatVariables;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FVector> VectorVariables;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FRotator> RotatorVariables;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FString> StringVariables;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, UObject*> ObjectVariables;
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class XYLOMODULARSPELLS_API UXMSSpellExecutorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UXMSSpellExecutorComponent();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSSpellExecutorComponent
	 */

/*--------------------------------------------------------------------------------------------------------------------*/
	// Variables

public:
	/** This function should handle all the value types registered in UXMSNodeDataRegistry */
	virtual void DefineVariable(const FString& Name, const FGameplayTag& Type);
	
	virtual void SetIntegerValue(const FString& Name, int32 Value);
	virtual bool GetIntegerValue(const FString& Name, int32& OutValue);
	
	virtual void SetFlotValue(const FString& Name, float Value);
	virtual bool GetFlotValue(const FString& Name, float& OutValue);
	
	virtual void SetVectorValue(const FString& Name, FVector Value);
	virtual bool GetVectorValue(const FString& Name, FVector& OutValue);
	
	virtual void SetRotatorValue(const FString& Name, FRotator Value);
	virtual bool GetRotatorValue(const FString& Name, FRotator& OutValue);
	
	virtual void SetStringValue(const FString& Name, FString Value);
	virtual bool GetStringValue(const FString& Name, FString& OutValue);
	
	virtual void SetObjectValue(const FString& Name, UObject* Value);
	virtual bool GetObjectValue(const FString& Name, UObject*& OutValue);
	
protected:
	UPROPERTY()
	FXMSSpellBrain Brain;

	// ~Variables
/*--------------------------------------------------------------------------------------------------------------------*/
	
};
