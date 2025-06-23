// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Runnable/Instruction/XMSVariableDefinitionNode.h"

#include "XMSTypes.h"
#include "Spell/XMSSpellExecutorInterface.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

void UXMSVariableDefinitionNode::OnRemovedFromParent()
{
	Super::OnRemovedFromParent();

	// TODO: unregister variable
}

void UXMSVariableDefinitionNode::OnSubNodeChanged(const FName& Identifier)
{
	Super::OnSubNodeChanged(Identifier);

	// TODO: Bind OnVariableTypeChanged and OnVariableNameChanged
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSRunnableNodeInterface Interface
 */

int32 UXMSVariableDefinitionNode::ExecuteNode()
{
	IXMSSpellExecutorInterface* SpellExecutor = Cast<IXMSSpellExecutorInterface>(GetOuter());
	if (!SpellExecutor) return 0;
	
	IXMSVariableTypeValueInterface* VariableTypeNode = VariableType.Get();
	if (!VariableTypeNode) return 0;

	IXMSStringValueInterface* VariableNameNode = VariableName.Get();
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
 * UXMSVariableDefinitionNode
 */

void UXMSVariableDefinitionNode::OnVariableTypeChanged(int32 NewType)
{
	// TODO: try change type of registered variable
}

void UXMSVariableDefinitionNode::OnVariableNameChanged(const FString& NewName, const FString& OldName)
{
	// TODO: if variable name is already used, then broadcast error to gui
	// TODO: call unregister for previous variable and register for new one
}

	
