// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell/XMSSpellActor.h"


AXMSSpellActor::AXMSSpellActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * AActor Interface
 */

void AXMSSpellActor::BeginPlay()
{
	Super::BeginPlay();

	if (IXMSRunnableNodeInterface* RunnableNodeInterface = Instruction.Get())
	{
		RunnableNodeInterface->ExecuteNode();
	}
}

void AXMSSpellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSSpellExecutorInterface Interface
 */

void AXMSSpellActor::SetIntegerValue(const FString& Name, int32 Value)
{
	Brain.IntegerVariables.Add(Name, Value);
}

bool AXMSSpellActor::GetIntegerValue(const FString& Name, int32& OutValue)
{
	int32* ValuePtr = Brain.IntegerVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void AXMSSpellActor::GetAllIntegerValueNames(TArray<FString>& OutNames)
{
	Brain.IntegerVariables.GetKeys(OutNames);
}

void AXMSSpellActor::SetFlotValue(const FString& Name, float Value)
{
	Brain.FloatVariables.Add(Name, Value);
}

bool AXMSSpellActor::GetFlotValue(const FString& Name, float& OutValue)
{
	float* ValuePtr = Brain.FloatVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void AXMSSpellActor::GetAllFloatValueNames(TArray<FString>& OutNames)
{
	Brain.FloatVariables.GetKeys(OutNames);
}

void AXMSSpellActor::SetVectorValue(const FString& Name, FVector Value)
{
	Brain.VectorVariables.Add(Name, Value);
}

bool AXMSSpellActor::GetVectorValue(const FString& Name, FVector& OutValue)
{
	FVector* ValuePtr = Brain.VectorVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void AXMSSpellActor::GetAllVectorValueNames(TArray<FString>& OutNames)
{
	Brain.VectorVariables.GetKeys(OutNames);
}

void AXMSSpellActor::SetRotatorValue(const FString& Name, FRotator Value)
{
	Brain.RotatorVariables.Add(Name, Value);
}

bool AXMSSpellActor::GetRotatorValue(const FString& Name, FRotator& OutValue)
{
	FRotator* ValuePtr = Brain.RotatorVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void AXMSSpellActor::GetAllRotatorValueNames(TArray<FString>& OutNames)
{
	Brain.RotatorVariables.GetKeys(OutNames);
}

void AXMSSpellActor::SetStringValue(const FString& Name, FString Value)
{
	Brain.StringVariables.Add(Name, Value);
}

bool AXMSSpellActor::GetStringValue(const FString& Name, FString& OutValue)
{
	FString* ValuePtr = Brain.StringVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void AXMSSpellActor::GetAllStringValueNames(TArray<FString>& OutNames)
{
	Brain.StringVariables.GetKeys(OutNames);
}

void AXMSSpellActor::SetObjectValue(const FString& Name, UObject* Value)
{
	Brain.ObjectVariables.Add(Name, Value);
}

bool AXMSSpellActor::GetObjectValue(const FString& Name, UObject*& OutValue)
{
	UObject** ValuePtr = Brain.ObjectVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void AXMSSpellActor::GetAllObjectValueNames(TArray<FString>& OutNames)
{
	Brain.ObjectVariables.GetKeys(OutNames);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * AXMSSpellActor
 */



