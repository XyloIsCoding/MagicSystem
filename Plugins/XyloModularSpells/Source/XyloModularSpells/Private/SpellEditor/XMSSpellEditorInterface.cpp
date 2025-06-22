// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellEditor/XMSSpellEditorInterface.h"

#include "XMSTypes.h"


void IXMSSpellEditorInterface::RegisterInScopeVariable(const FString& Name, int32 VariableType)
{
}

void IXMSSpellEditorInterface::UnregisterInScopeVariable(const FString& Name)
{
}

void IXMSSpellEditorInterface::ChangeInScopeVariableType(const FString& Name, int32 VariableType)
{
}

void IXMSSpellEditorInterface::GetInScopeVariablesByType(int32 VariableType, TArray<FString>& OutVariablesNames)
{
}
