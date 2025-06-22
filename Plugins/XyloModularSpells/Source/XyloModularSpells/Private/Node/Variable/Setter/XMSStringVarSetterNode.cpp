// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Variable/Setter/XMSStringVarSetterNode.h"

#include "Spell/XMSSpellExecutorInterface.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSVariableSetterInterface Interface
 */

bool UXMSStringVarSetterNode::SetVariable()
{
	IXMSSpellExecutorInterface* SpellExecutor = Cast<IXMSSpellExecutorInterface>(GetOuter());
	if (!SpellExecutor) return false;

	IXMSStringValueInterface* VariableNameNode = VariableName.Get();
	if (!VariableNameNode) return false;

	IXMSStringValueInterface* Value = StringValue.Get();
	if (!Value) return false;

	FString VariableNameString;
	if (!VariableNameNode->GetString(VariableNameString)) return false;
	if (VariableNameString.IsEmpty()) return false;

	FString VariableValueString;
	if (!Value->GetString(VariableValueString)) return false;
	
	SpellExecutor->SetStringValue(VariableNameString, VariableValueString);
	return true;
}
