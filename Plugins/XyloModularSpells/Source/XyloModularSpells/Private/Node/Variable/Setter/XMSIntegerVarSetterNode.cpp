// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Variable/Setter/XMSIntegerVarSetterNode.h"

#include "XMSTypes.h"
#include "Spell/XMSSpellExecutorInterface.h"
#include "SpellEditor/XMSSpellEditorInterface.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

void UXMSIntegerVarSetterNode::OnSubNodeChanged(const FName& Identifier)
{
	Super::OnSubNodeChanged(Identifier);

	if (Identifier.IsEqual(GET_MEMBER_NAME_CHECKED(ThisClass, VariableName)))
	{
		if (UXMSVariableNameNode* VariableNameNode = Cast<UXMSVariableNameNode>(VariableName.Get()))
		{
			VariableNameNode->SetType(XMSVariableType::EVT_Integer);
		}
	}
}

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
	
	FString VariableNameString;
	if (!VariableNameNode->GetString(VariableNameString)) return false;
	if (VariableNameString.IsEmpty()) return false;
	
	SpellExecutor->SetIntegerValue(VariableNameString, Value->GetInteger());
	return true;
}
