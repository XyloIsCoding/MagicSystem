// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Runnable/Instruction/XMSVariableDefinitionNode.h"

#include "XMSTypes.h"
#include "Spell/XMSSpellExecutorInterface.h"


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

	bool bStringFound;
	FString VariableNameString = VariableNameNode->GetString(bStringFound);
	if (!bStringFound) return 0;
	
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

	
