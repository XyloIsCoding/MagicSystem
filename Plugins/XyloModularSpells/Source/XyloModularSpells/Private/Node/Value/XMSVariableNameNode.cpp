// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Value/XMSVariableNameNode.h"

#include "XMSNodeStaticLibrary.h"
#include "SpellEditor/XMSSpellEditorComponent.h"
#include "SpellEditor/XMSSpellEditorInterface.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSVariableNameNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);

	NodeJson->SetStringField(ValueJsonKey, CachedName);

	// Only serialize StringIndex if we are editing the spell
	if (IsInSpellEditorContext())
	{
		NodeJson->SetNumberField(TEXT("EditorVariableType"), VariableType);
	}
	
	return NodeJson;
}

void UXMSVariableNameNode::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);

	JsonObject->TryGetStringField(ValueJsonKey, CachedName);

	// Only deserialize StringIndex if we are editing the spell
	if (IsInSpellEditorContext())
	{
		JsonObject->TryGetNumberField(TEXT("EditorVariableType"), VariableType);
	}
}

void UXMSVariableNameNode::OnParentSet()
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

bool UXMSVariableNameNode::GetString(FString& OutString)
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

void UXMSVariableNameNode::OnDeclaredVariablesListChanged(const FString& NewVariableName, int32 NewVariableType, const FString& OldVariableName, int32 OldVariableType)
{
	if (NewVariableType != VariableType && OldVariableType != VariableType) return;

	// Declared variable list changed for the variable type of this node, so we want to check if the CachedName is
	// still a valid option, else we reset CachedName
	TArray<FString> Strings;
	GetOptions(Strings);
	if (!Strings.Contains(CachedName))
	{
		CacheString(-1);
	}
}

void UXMSVariableNameNode::SelectByIndex(int32 InStringIndex)
{
	if (!IsInSpellEditorContext()) return;
	
	CacheString(InStringIndex);
}

void UXMSVariableNameNode::SetType(int32 InVariableType)
{
	if (!IsInSpellEditorContext()) return;
	
	VariableType = InVariableType;
	// We use -1 because we do not want a random variable to be selected without the user noticing,
	// so we ask to cache an empty string so gui can show error.
	CacheString(-1);
}

void UXMSVariableNameNode::GetOptions(TArray<FString>& OutStringOptions) const
{
	UXMSSpellEditorComponent* SpellEditor = UXMSNodeStaticLibrary::GetSpellEditorComponent(GetOuter());
	if (!SpellEditor) return;
	
	SpellEditor->GetVariablesNamesByType(VariableType, this, OutStringOptions);
}

void UXMSVariableNameNode::CacheString(int32 Index)
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
