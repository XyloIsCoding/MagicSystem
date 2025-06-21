// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Variable/Setter/XMSIntegerVarSetterNode.h"

#include "Spell/XMSSpellExecutorInterface.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSVariableSetterInterface Interface
 */

bool UXMSIntegerVarSetterNode::SetVariable()
{
	IXMSSpellExecutorInterface* SpellExecutor = Cast<IXMSSpellExecutorInterface>(GetOuter());
	if (!SpellExecutor) return false;

	IXMSStringValueInterface* VariableNameNode = VariableName.Get();
	if (!VariableNameNode) return false;

	IXMSIntegerValueInterface* Value = IntegerValue.Get();
	if (!Value) return false;

	bool bStringFound;
	FString VariableNameString = VariableNameNode->GetString(bStringFound);
	if (!bStringFound) return false;
	
	SpellExecutor->SetIntegerValue(VariableNameString, Value->GetInteger());
	return true;
}
