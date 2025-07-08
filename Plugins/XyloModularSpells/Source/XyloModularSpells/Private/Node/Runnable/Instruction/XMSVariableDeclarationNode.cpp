// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Runnable/Instruction/XMSVariableDeclarationNode.h"

#include "XMSNodeStaticLibrary.h"
#include "XMSTypes.h"
#include "Node/Variable/XMSVariableNameValueNode.h"
#include "SpellExecutor/XMSSpellExecutorInterface.h"
#include "SpellEditor/XMSSpellEditorComponent.h"
#include "SpellExecutor/XMSSpellExecutorComponent.h"


UXMSVariableDeclarationNode::UXMSVariableDeclarationNode()
{
	VariableType.Set(NewObject<UXMSValueTypeValueNode>(GetOuter()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

void UXMSVariableDeclarationNode::PreRemovedFromParent()
{
	Super::PreRemovedFromParent();

	if (UXMSSpellEditorComponent* SpellEditor = UXMSNodeStaticLibrary::GetSpellEditorComponent(GetOuter()))
	{
		SpellEditor->UnRegisterVariable(this);
	}
}

void UXMSVariableDeclarationNode::OnSubNodeChanged(FName Identifier)
{
	Super::OnSubNodeChanged(Identifier);

	// We do not need to deal with OnVariableTypeChanged and OnVariableNameChanged outside of editor
	if (!IsInSpellEditorContext()) return;
	
	if (Identifier.IsEqual(GET_MEMBER_NAME_CHECKED(ThisClass, VariableType)))
	{
		if (UXMSValueTypeValueNode* VariableTypeNode = VariableType.Get())
		{
			// Bind delegate
			VariableTypeNode->ValueTypeChangedDelegate.AddUObject(this, &ThisClass::OnVariableTypeChanged);

			// Set initial value
			OnVariableTypeChanged(VariableTypeNode->GetValueType(), XMSValueType::None);
		}
	}

	if (Identifier.IsEqual(GET_MEMBER_NAME_CHECKED(ThisClass, VariableName)))
	{
		if (UXMSStringValueNode* StringValueNode = VariableName.Get())
		{
			// Bind delegate
			StringValueNode->StringValueChangedDelegate.AddUObject(this, &ThisClass::OnVariableNameChanged);

			// Set initial value
			FString StringValue;
			if (StringValueNode->GetString(StringValue))
			{
				OnVariableNameChanged(StringValue, FString());
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSRunnableNodeInterface Interface
 */

int32 UXMSVariableDeclarationNode::ExecuteNode()
{
	UXMSSpellExecutorComponent* SpellExecutor = UXMSNodeStaticLibrary::GetSpellExecutorComponent(GetOuter());
	if (!SpellExecutor) return 0;
	
	IXMSValueTypeValueInterface* VariableTypeNode = VariableType.GetInterface();
	if (!VariableTypeNode) return 0;

	IXMSStringValueInterface* VariableNameNode = VariableName.GetInterface();
	if (!VariableNameNode) return 0;
	
	FString VariableNameString;
	if (!VariableNameNode->GetString(VariableNameString)) return 0;
	if (VariableNameString.IsEmpty()) return 0;

	SpellExecutor->DefineVariable(VariableNameString, VariableTypeNode->GetValueType());
	return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSVariableDeclarationNode
 */

void UXMSVariableDeclarationNode::OnVariableTypeChanged(const FGameplayTag& NewType, const FGameplayTag& OldType)
{
	if (UXMSSpellEditorComponent* SpellEditor = UXMSNodeStaticLibrary::GetSpellEditorComponent(GetOuter()))
	{
		SpellEditor->UpdateVariableType(this, NewType);
	}
}

void UXMSVariableDeclarationNode::OnVariableNameChanged(const FString& NewName, const FString& OldName)
{
	if (NewName.IsEmpty())
	{
		// TODO: gui error
		return;
	}
	
	if (UXMSSpellEditorComponent* SpellEditor = UXMSNodeStaticLibrary::GetSpellEditorComponent(GetOuter()))
	{
		IXMSValueTypeValueInterface* VariableTypeNode = VariableType.GetInterface();
		if (!VariableTypeNode) return;
		
		SpellEditor->RegisterOrUpdateVariable(this, NewName, VariableTypeNode->GetValueType());

		// TODO: if variable name is already used, then broadcast error to gui
	}
}

	
