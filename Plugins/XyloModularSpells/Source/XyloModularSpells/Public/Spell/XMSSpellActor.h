// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSSpellExecutorInterface.h"
#include "GameFramework/Actor.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Runnable/XMSRunnableNodeInterface.h"
#include "XMSSpellActor.generated.h"


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


class UBlackboardComponent;
class UBlackboardData;

UCLASS()
class XYLOMODULARSPELLS_API AXMSSpellActor : public AActor, public IXMSSpellExecutorInterface
{
	GENERATED_BODY()

public:
	AXMSSpellActor();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * AActor Interface
	 */

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSSpellExecutorInterface Interface
	 */

public:
	virtual void SetIntegerValue(const FString& Name, int32 Value) override;
	virtual bool GetIntegerValue(const FString& Name, int32& OutValue) override;
	virtual void GetAllIntegerValueNames(TArray<FString>& OutNames) override;
	
	virtual void SetFlotValue(const FString& Name, float Value) override;
	virtual bool GetFlotValue(const FString& Name, float& OutValue) override;
	virtual void GetAllFloatValueNames(TArray<FString>& OutNames) override;
	
	virtual void SetVectorValue(const FString& Name, FVector Value) override;
	virtual bool GetVectorValue(const FString& Name, FVector& OutValue) override;
	virtual void GetAllVectorValueNames(TArray<FString>& OutNames) override;
	
	virtual void SetRotatorValue(const FString& Name, FRotator Value) override;
	virtual bool GetRotatorValue(const FString& Name, FRotator& OutValue) override;
	virtual void GetAllRotatorValueNames(TArray<FString>& OutNames) override;
	
	virtual void SetStringValue(const FString& Name, FString Value) override;
	virtual bool GetStringValue(const FString& Name, FString& OutValue) override;
	virtual void GetAllStringValueNames(TArray<FString>& OutNames) override;

	virtual void SetObjectValue(const FString& Name, UObject* Value) override;
	virtual bool GetObjectValue(const FString& Name, UObject*& OutValue) override;
	virtual void GetAllObjectValueNames(TArray<FString>& OutNames) override;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * AXMSSpellActor
	 */

protected:
	UPROPERTY()
	FXMSSpellBrain Brain;
	
public:
	TXMSNodeContainer<UXMSNode, IXMSRunnableNodeInterface> Instruction = {
		nullptr,
		GET_MEMBER_NAME_CHECKED(ThisClass, Instruction),
		[](UClass* NodeClass){ return true; } };
};
