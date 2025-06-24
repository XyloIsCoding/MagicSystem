// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Variable/Setter/XMSStringVarSetterNode.h"

#include "XMSTypes.h"
#include "Spell/XMSSpellExecutorInterface.h"
#include "SpellEditor/XMSSpellEditorInterface.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

void UXMSStringVarSetterNode::OnSubNodeChanged(FName Identifier)
{
	Super::OnSubNodeChanged(Identifier);

	if (Identifier.IsEqual(GET_MEMBER_NAME_CHECKED(ThisClass, VariableName)))
	{
		if (UXMSVariableNameNode* VariableNameNode = VariableName.Get())
		{
			VariableNameNode->SetType(XMSVariableType::EVT_String);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSVariableSetterInterface Interface
 */

bool UXMSStringVarSetterNode::SetVariable()
{
	IXMSSpellExecutorInterface* SpellExecutor = Cast<IXMSSpellExecutorInterface>(GetOuter());
	if (!SpellExecutor) return false;

	IXMSStringValueInterface* VariableNameNode = VariableName.GetInterface();
	if (!VariableNameNode) return false;

	IXMSStringValueInterface* Value = StringValue.GetInterface();
	if (!Value) return false;

	FString VariableNameString;
	if (!VariableNameNode->GetString(VariableNameString)) return false;
	if (VariableNameString.IsEmpty()) return false;

	FString VariableValueString;
	if (!Value->GetString(VariableValueString)) return false;
	
	SpellExecutor->SetStringValue(VariableNameString, VariableValueString);
	return true;
}
