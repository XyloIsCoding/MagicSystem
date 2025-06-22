// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSSpellEditorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSSpellEditorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSSpellEditorInterface
{
	GENERATED_BODY()

public:
	virtual void RegisterInScopeVariable(const FString& Name, int32 VariableType);
	virtual void UnregisterInScopeVariable(const FString& Name);
	virtual void ChangeInScopeVariableType(const FString& Name, int32 VariableType);
	virtual void GetInScopeVariablesByType(int32 VariableType, TArray<FString>& OutVariablesNames);
};
