// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellExecutor/XMSSpellExecutorComponent.h"

#include "GameplayTagContainer.h"
#include "XMSTypes.h"


UXMSSpellExecutorComponent::UXMSSpellExecutorComponent()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSSpellExecutorComponent
 */

/*--------------------------------------------------------------------------------------------------------------------*/
// Variables

void UXMSSpellExecutorComponent::DefineVariable(const FString& Name, const FGameplayTag& Type)
{
	if (Type.MatchesTagExact(XMSValueType::Integer))
	{
		SetIntegerValue(Name, 0);
		return;
	}

	if (Type.MatchesTagExact(XMSValueType::Float))
	{
		SetFlotValue(Name, 0.f);
		return;
	}

	if (Type.MatchesTagExact(XMSValueType::Vector))
	{
		SetVectorValue(Name, FVector::ZeroVector);
		return;
	}

	if (Type.MatchesTagExact(XMSValueType::Rotator))
	{
		SetRotatorValue(Name, FRotator::ZeroRotator);
		return;
	}

	if (Type.MatchesTagExact(XMSValueType::String))
	{
		SetStringValue(Name, FString());
		return;
	}

	if (Type.MatchesTagExact(XMSValueType::Object))
	{
		SetObjectValue(Name, nullptr);
		return;
	}
}

void UXMSSpellExecutorComponent::SetBoolValue(const FString& Name, bool Value)
{
	Brain.BoolVariables.Add(Name, Value);
}

bool UXMSSpellExecutorComponent::GetBoolValue(const FString& Name, bool& OutValue)
{
	bool* ValuePtr = Brain.BoolVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void UXMSSpellExecutorComponent::SetIntegerValue(const FString& Name, int32 Value)
{
	Brain.IntegerVariables.Add(Name, Value);
}

bool UXMSSpellExecutorComponent::GetIntegerValue(const FString& Name, int32& OutValue)
{
	int32* ValuePtr = Brain.IntegerVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void UXMSSpellExecutorComponent::SetFlotValue(const FString& Name, float Value)
{
	Brain.FloatVariables.Add(Name, Value);
}

bool UXMSSpellExecutorComponent::GetFlotValue(const FString& Name, float& OutValue)
{
	float* ValuePtr = Brain.FloatVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void UXMSSpellExecutorComponent::SetVectorValue(const FString& Name, FVector Value)
{
	Brain.VectorVariables.Add(Name, Value);
}

bool UXMSSpellExecutorComponent::GetVectorValue(const FString& Name, FVector& OutValue)
{
	FVector* ValuePtr = Brain.VectorVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void UXMSSpellExecutorComponent::SetRotatorValue(const FString& Name, FRotator Value)
{
	Brain.RotatorVariables.Add(Name, Value);
}

bool UXMSSpellExecutorComponent::GetRotatorValue(const FString& Name, FRotator& OutValue)
{
	FRotator* ValuePtr = Brain.RotatorVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void UXMSSpellExecutorComponent::SetStringValue(const FString& Name, FString Value)
{
	Brain.StringVariables.Add(Name, Value);
}

bool UXMSSpellExecutorComponent::GetStringValue(const FString& Name, FString& OutValue)
{
	FString* ValuePtr = Brain.StringVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

void UXMSSpellExecutorComponent::SetObjectValue(const FString& Name, UObject* Value)
{
	Brain.ObjectVariables.Add(Name, Value);
}

bool UXMSSpellExecutorComponent::GetObjectValue(const FString& Name, UObject*& OutValue)
{
	UObject** ValuePtr = Brain.ObjectVariables.Find(Name);
	if (!ValuePtr) return false;
	
	OutValue = *ValuePtr;
	return true;
}

// ~Variables
/*--------------------------------------------------------------------------------------------------------------------*/

