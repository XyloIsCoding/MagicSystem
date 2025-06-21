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
}

void AXMSSpellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSSpellExecutorInterface Interface
 */

void AXMSSpellActor::SetIntegerValue(FString Name, int32 Value)
{
	Brain.IntegerVariables.Add(Name, Value);
}

bool AXMSSpellActor::GetIntegerValue(FString Name, int32& OutValue)
{
	int32* ValuePtr = Brain.IntegerVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void AXMSSpellActor::SetFlotValue(FString Name, float Value)
{
	Brain.FloatVariables.Add(Name, Value);
}

bool AXMSSpellActor::GetFlotValue(FString Name, float& OutValue)
{
	float* ValuePtr = Brain.FloatVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void AXMSSpellActor::SetVectorValue(FString Name, FVector Value)
{
	Brain.VectorVariables.Add(Name, Value);
}

bool AXMSSpellActor::GetVectorValue(FString Name, FVector& OutValue)
{
	FVector* ValuePtr = Brain.VectorVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void AXMSSpellActor::SetRotatorValue(FString Name, FRotator Value)
{
	Brain.RotatorVariables.Add(Name, Value);
}

bool AXMSSpellActor::GetRotatorValue(FString Name, FRotator& OutValue)
{
	FRotator* ValuePtr = Brain.RotatorVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void AXMSSpellActor::SetStringValue(FString Name, FString Value)
{
	Brain.StringVariables.Add(Name, Value);
}

bool AXMSSpellActor::GetStringValue(FString Name, FString& OutValue)
{
	FString* ValuePtr = Brain.StringVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void AXMSSpellActor::SetObjectValue(FString Name, UObject* Value)
{
	Brain.ObjectVariables.Add(Name, Value);
}

bool AXMSSpellActor::GetObjectValue(FString Name, UObject*& OutValue)
{
	UObject** ValuePtr = Brain.ObjectVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * AXMSSpellActor
 */



