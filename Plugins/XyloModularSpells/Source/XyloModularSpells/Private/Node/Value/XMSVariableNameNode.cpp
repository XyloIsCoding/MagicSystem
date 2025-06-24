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
		NodeJson->SetNumberField(TEXT("EditorStringIndex"), StringIndex);
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
		JsonObject->TryGetNumberField(TEXT("EditorStringIndex"), StringIndex);
		JsonObject->TryGetNumberField(TEXT("EditorVariableType"), VariableType);
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

void UXMSVariableNameNode::SetStringIndex(int32 InStringIndex)
{
	if (!IsInSpellEditorContext()) return;
	
	StringIndex = InStringIndex;
	CacheString();
}

void UXMSVariableNameNode::SetType(int32 InVariableType)
{
	if (!IsInSpellEditorContext()) return;
	
	VariableType = InVariableType;
	CacheString();
}

void UXMSVariableNameNode::GetOptions(TArray<FString>& OutStringOptions) const
{
	UXMSSpellEditorComponent* SpellEditor = UXMSNodeStaticLibrary::GetSpellEditorComponent(GetOuter());
	if (!SpellEditor) return;
	
	SpellEditor->GetVariablesNamesByType(VariableType, this, OutStringOptions);
}

void UXMSVariableNameNode::CacheString()
{
	FString OldName = CachedName;
	
	TArray<FString> Strings;
	GetOptions(Strings);
	if (Strings.IsValidIndex(StringIndex))
	{
		CachedName = Strings[StringIndex];
	}
	else
	{
		CachedName.Empty();
	}

	VariableNameChangedDelegate.Broadcast(CachedName, OldName);
}
