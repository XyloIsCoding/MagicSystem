// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Variable/XMSVariableNameValueNode.h"

#include "XMSNodeStaticLibrary.h"
#include "SpellEditor/XMSSpellEditorComponent.h"
#include "SpellEditor/XMSSpellEditorInterface.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSVariableNameValueNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);

	NodeJson->SetStringField(ValueJsonKey, CachedName);

	return NodeJson;
}

void UXMSVariableNameValueNode::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);

	JsonObject->TryGetStringField(ValueJsonKey, CachedName);
}

void UXMSVariableNameValueNode::OnParentSet()
{
	Super::OnParentSet();

	if (UXMSSpellEditorComponent* SpellEditor = UXMSNodeStaticLibrary::GetSpellEditorComponent(GetOuter()))
	{
		SpellEditor->DeclaredVariableListChangedDelegate.AddUObject(this, &ThisClass::OnDeclaredVariablesListChanged);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSStringValueInterface Interface
 */

bool UXMSVariableNameValueNode::GetString(FString& OutString)
{
	if (CachedName.IsEmpty())
	{
		return false;
	}
	
	OutString = CachedName;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSStringValueNode
 */

void UXMSVariableNameValueNode::OnDeclaredVariablesListChanged(const FString& NewVariableName, const FGameplayTag& NewVariableType, const FString& OldVariableName, const FGameplayTag& OldVariableType)
{
	if (!NewVariableType.MatchesTagExact(VariableType) && !OldVariableType.MatchesTagExact(VariableType)) return;

	// Declared variable list changed for the variable type of this node, so we want to check if the CachedName is
	// still a valid option, else we reset CachedName
	TArray<FString> Strings;
	GetOptions(Strings);
	if (!Strings.Contains(CachedName))
	{
		CacheString(-1);
	}
}

void UXMSVariableNameValueNode::SelectByIndex(int32 InStringIndex)
{
	if (!IsInSpellEditorContext()) return;
	
	CacheString(InStringIndex);
}

void UXMSVariableNameValueNode::SetType(const FGameplayTag& InVariableType)
{
	if (!IsInSpellEditorContext()) return;
	
	VariableType = InVariableType;
	// We use -1 because we do not want a random variable to be selected without the user noticing,
	// so we ask to cache an empty string so gui can show error.
	CacheString(-1);
}

void UXMSVariableNameValueNode::GetOptions(TArray<FString>& OutStringOptions) const
{
	UXMSSpellEditorComponent* SpellEditor = UXMSNodeStaticLibrary::GetSpellEditorComponent(GetOuter());
	if (!SpellEditor) return;
	
	SpellEditor->GetVariablesNamesByType(this, VariableType, OutStringOptions);
}

void UXMSVariableNameValueNode::CacheString(int32 Index)
{
	FString OldName = CachedName;

	if (Index >= 0)
	{
		TArray<FString> Strings;
		GetOptions(Strings);
		if (Strings.IsValidIndex(Index))
		{
			CachedName = Strings[Index];
		}
		else
		{
			CachedName.Empty();
		}
	}
	else
	{
		CachedName.Empty();
	}
	
	VariableNameChangedDelegate.Broadcast(CachedName, OldName);
}
