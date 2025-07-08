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
		InvalidateName();
	}
}

void UXMSVariableNameValueNode::SetType(const FGameplayTag& InVariableType)
{
	if (!IsInSpellEditorContext()) return;
	
	VariableType = InVariableType;
	InvalidateName();
}

void UXMSVariableNameValueNode::GetOptions(TArray<FString>& OutStringOptions) const
{
	UXMSSpellEditorComponent* SpellEditor = UXMSNodeStaticLibrary::GetSpellEditorComponent(GetOuter());
	if (!SpellEditor) return;
	
	SpellEditor->GetVariablesNamesByType(this, VariableType, OutStringOptions);
}

void UXMSVariableNameValueNode::SetName(const FString& InName)
{
	if (InName.IsEmpty())
	{
		InvalidateName();
		return;
	}
	
	TArray<FString> Options;
	GetOptions(Options);
	if (!Options.Contains(InName))
	{
		InvalidateName();
		return;
	}
	
	FString OldName = CachedName;
	CachedName = InName;
	VariableNameChangedDelegate.Broadcast(CachedName, OldName);
}

void UXMSVariableNameValueNode::InvalidateName()
{
	FString OldName = CachedName;
	CachedName.Empty();
	VariableNameChangedDelegate.Broadcast(CachedName, OldName);
}

