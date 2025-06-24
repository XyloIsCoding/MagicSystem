// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Variable/Getter/XMSIntegerVarGetterNode.h"

#include "XMSTypes.h"
#include "Spell/XMSSpellExecutorInterface.h"
#include "SpellEditor/XMSSpellEditorInterface.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

void UXMSIntegerVarGetterNode::OnSubNodeChanged(FName Identifier)
{
	Super::OnSubNodeChanged(Identifier);

	if (Identifier.IsEqual(GET_MEMBER_NAME_CHECKED(ThisClass, VariableName)))
	{
		if (UXMSVariableNameNode* VariableNameNode = VariableName.Get())
		{
			VariableNameNode->SetType(XMSVariableType::EVT_Integer);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSIntegerValueInterface Interface
 */

int32 UXMSIntegerVarGetterNode::GetInteger()
{
	IXMSSpellExecutorInterface* SpellExecutor = Cast<IXMSSpellExecutorInterface>(GetOuter());
	if (!SpellExecutor)
	{
		return 0;
	}

	IXMSStringValueInterface* VariableNameNode = VariableName.GetInterface();
	if (!VariableNameNode)
	{
		return 0;
	}
	
	FString VariableNameString;
	if (!VariableNameNode->GetString(VariableNameString))
	{
		return 0;
	}

	int32 VariableValueInt;
	if (!SpellExecutor->GetIntegerValue(VariableNameString, VariableValueInt))
	{
		return  0;
	}
	
	return VariableValueInt;
}
