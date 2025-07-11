// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Variable/XMSVariableNameValueNode.h"

#include "XMSNodeStaticLibrary.h"
#include "SpellEditor/XMSSpellEditorComponent.h"
#include "SpellEditor/XMSSpellEditorInterface.h"


bool FXMSCachedVariableName::GetValidName(FString& OutName)
{
	if (!bValidName) return false;
	
	OutName = CachedName;
	return true;
}

void FXMSCachedVariableName::SetName(const FString& InName)
{
	CachedName = InName;
	bValidName = true;
}

void FXMSCachedVariableName::InvalidateName()
{
	bValidName = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

TSharedPtr<FJsonObject> UXMSVariableNameValueNode::SerializeToJson(bool& bOutSuccess)
{
	TSharedPtr<FJsonObject> NodeJson = Super::SerializeToJson(bOutSuccess);

	// We serialize the CachedName regardless if it is valid or not even in editor.
	// If we are in editor, the validity will be checked on deserialization.
	// If we are in executor context, a valid name will have no different consequence than an empty name.
	NodeJson->SetStringField(ValueJsonKey, CachedVariableName.GetName());

	return NodeJson;
}

void UXMSVariableNameValueNode::DeserializeFromJson(TSharedPtr<FJsonObject> JsonObject)
{
	Super::DeserializeFromJson(JsonObject);

	FString CachedName;
	JsonObject->TryGetStringField(ValueJsonKey, CachedName);
	CachedVariableName.SetName(CachedName);

	// SetName does not change the CachedName if it is invalid. So it is important that even in spell editor
	// we manually set the CachedName before calling SetName, else we will be unable to broadcast the invalid
	// cached name for UI usage, or restore the name if it becomes valid again.
	if (IsInSpellEditorContext()) SetName(CachedName);
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
	return CachedVariableName.GetValidName(OutString);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSStringValueNode
 */

void UXMSVariableNameValueNode::OnDeclaredVariablesListChanged(const FString& NewVariableName, const FGameplayTag& NewVariableType, const FString& OldVariableName, const FGameplayTag& OldVariableType)
{
	if (!NewVariableType.MatchesTagExact(VariableType) && !OldVariableType.MatchesTagExact(VariableType)) return;

	// Declared variable list changed for the variable type of this node, so we want to check if the CachedName is
	// still a valid option, or became one
	SetName(CachedVariableName.GetName());
}

void UXMSVariableNameValueNode::SetType(const FGameplayTag& InVariableType)
{
	checkf(IsInSpellEditorContext(), TEXT("UXMSVariableNameValueNode::SetType >> Can only be called in spell editor context"))
	
	VariableType = InVariableType;
	SetName(CachedVariableName.GetName());
}

void UXMSVariableNameValueNode::GetOptions(TArray<FString>& OutStringOptions) const
{
	UXMSSpellEditorComponent* SpellEditor = UXMSNodeStaticLibrary::GetSpellEditorComponent(GetOuter());
	if (!SpellEditor) return;
	
	SpellEditor->GetVariablesNamesByType(this, VariableType, OutStringOptions);
}

void UXMSVariableNameValueNode::BroadcastVariableNameChangedDelegate(const FString& OldName)
{
	if (CachedVariableName.IsValidName())
	{
		VariableNameChangedDelegate.Broadcast(CachedVariableName.GetName(), OldName, true);
	}
	else
	{
		VariableNameChangedDelegate.Broadcast(FString(), CachedVariableName.GetName(), false);
	}
}

bool UXMSVariableNameValueNode::GetLastValidName(FString& OutName)
{
	OutName = CachedVariableName.GetName();
	return CachedVariableName.IsValidName();
}

void UXMSVariableNameValueNode::SetName(const FString& InName)
{
	checkf(IsInSpellEditorContext(), TEXT("UXMSVariableNameValueNode::SetName >> Can only be called in spell editor context"))
	
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

	FString OldName = CachedVariableName.GetName();
	CachedVariableName.SetName(InName);
	BroadcastVariableNameChangedDelegate(OldName);
}

void UXMSVariableNameValueNode::InvalidateName()
{
	checkf(IsInSpellEditorContext(), TEXT("UXMSVariableNameValueNode::InvalidateName >> Can only be called in spell editor context"))
	
	CachedVariableName.InvalidateName();
	BroadcastVariableNameChangedDelegate();
}

