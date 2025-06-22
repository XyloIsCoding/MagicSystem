// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Value/XMSVariableNameNode.h"

#include "SpellEditor/XMSSpellEditorInterface.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSVariableNameNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);

	NodeJson->SetStringField(ValueJsonKey, CachedString);

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

	JsonObject->TryGetStringField(ValueJsonKey, CachedString);

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
	if (CachedString.IsEmpty())
	{
		return false;
	}
	
	OutString = CachedString;
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
	IXMSSpellEditorInterface* SpellEditor = Cast<IXMSSpellEditorInterface>(GetOuter());
	if (!SpellEditor) return;
	
	SpellEditor->GetInScopeVariablesByType(VariableType, OutStringOptions);
}

void UXMSVariableNameNode::CacheString()
{
	TArray<FString> Strings;
	GetOptions(Strings);
	if (!Strings.IsValidIndex(StringIndex))
	{
		CachedString.Empty();	
	}

	CachedString = Strings[StringIndex];
}
