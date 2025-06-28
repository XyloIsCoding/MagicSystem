// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Runnable/Instruction/XMSVariableDeclarationNode.h"

#include "XMSNodeStaticLibrary.h"
#include "XMSTypes.h"
#include "Node/Value/XMSVariableNameNode.h"
#include "Spell/XMSSpellExecutorInterface.h"
#include "SpellEditor/XMSSpellEditorComponent.h"


UXMSVariableDeclarationNode::UXMSVariableDeclarationNode()
{
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
		if (UXMSVariableTypeValueNode* VariableTypeNode = VariableType.Get())
		{
			// Bind delegate
			VariableTypeNode->VariableTypeChangedDelegate.AddUObject(this, &ThisClass::OnVariableTypeChanged);

			// Set initial value
			OnVariableTypeChanged(VariableTypeNode->GetVariableType(), XMSVariableType::EVT_None);
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
	IXMSSpellExecutorInterface* SpellExecutor = Cast<IXMSSpellExecutorInterface>(GetOuter());
	if (!SpellExecutor) return 0;
	
	IXMSVariableTypeValueInterface* VariableTypeNode = VariableType.GetInterface();
	if (!VariableTypeNode) return 0;

	IXMSStringValueInterface* VariableNameNode = VariableName.GetInterface();
	if (!VariableNameNode) return 0;
	
	FString VariableNameString;
	if (!VariableNameNode->GetString(VariableNameString)) return 0;
	if (VariableNameString.IsEmpty()) return 0;
	
	switch (VariableTypeNode->GetVariableType())
	{
	case XMSVariableType::EVT_Integer :
		SpellExecutor->SetIntegerValue(VariableNameString, 0);
		break;
	case XMSVariableType::EVT_Float :
		SpellExecutor->SetFlotValue(VariableNameString, 0.f);
		break;
	case XMSVariableType::EVT_Vector :
		SpellExecutor->SetVectorValue(VariableNameString, FVector::ZeroVector);
		break;
	case XMSVariableType::EVT_Rotator :
		SpellExecutor->SetRotatorValue(VariableNameString, FRotator::ZeroRotator);
		break;
	case XMSVariableType::EVT_String :
		SpellExecutor->SetStringValue(VariableNameString, FString());
		break;
	case XMSVariableType::EVT_Object :
		SpellExecutor->SetObjectValue(VariableNameString, nullptr);
		break;
	default:
		return 0;
	}

	return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSVariableDeclarationNode
 */

void UXMSVariableDeclarationNode::OnVariableTypeChanged(int32 NewType, int32 OldType)
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
		IXMSVariableTypeValueInterface* VariableTypeNode = VariableType.GetInterface();
		if (!VariableTypeNode) return;
		
		SpellEditor->RegisterOrUpdateVariable(this, NewName, VariableTypeNode->GetVariableType());

		// TODO: if variable name is already used, then broadcast error to gui
	}
}

	
