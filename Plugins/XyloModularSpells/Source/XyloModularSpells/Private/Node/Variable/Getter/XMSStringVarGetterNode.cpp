// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Variable/Getter/XMSStringVarGetterNode.h"

#include "XMSTypes.h"
#include "Spell/XMSSpellExecutorInterface.h"
#include "SpellEditor/XMSSpellEditorInterface.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

void UXMSStringVarGetterNode::OnSubNodeChanged(FName Identifier)
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
 * IXMSStringValueInterface Interface
 */

bool UXMSStringVarGetterNode::GetString(FString& OutString)
{
	IXMSSpellExecutorInterface* SpellExecutor = Cast<IXMSSpellExecutorInterface>(GetOuter());
	if (!SpellExecutor)
	{
		OutString = FString(TEXT("ERROR: UXMSStringVarGetterNode::GetString >> Failed to get string variable!"));
		return false;
	}

	IXMSStringValueInterface* VariableNameNode = VariableName.GetInterface();
	if (!VariableNameNode)
	{
		OutString = FString(TEXT("ERROR: UXMSStringVarGetterNode::GetString >> Failed to get string variable!"));
		return false;
	}
	
	FString VariableNameString;
	if (!VariableNameNode->GetString(VariableNameString))
	{
		OutString = FString(TEXT("ERROR: UXMSStringVarGetterNode::GetString >> Failed to get string variable!"));
		return false;
	}

	FString VariableValueString;
	if (!SpellExecutor->GetStringValue(VariableNameString, VariableValueString))
	{
		OutString = FString(TEXT("ERROR: UXMSStringVarGetterNode::GetString >> Failed to get string variable!"));
		return false;
	}
	
	OutString = VariableValueString;
	return false;
}
