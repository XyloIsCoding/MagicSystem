// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/String/Variable/XMSStringVarGetterNode.h"

#include "XMSNodeStaticLibrary.h"
#include "XMSTypes.h"
#include "SpellExecutor/XMSSpellExecutorInterface.h"
#include "SpellEditor/XMSSpellEditorInterface.h"
#include "SpellExecutor/XMSSpellExecutorComponent.h"


UXMSStringVarGetterNode::UXMSStringVarGetterNode()
{
	VariableName.Set(NewObject<UXMSVariableNameValueNode>(GetOuter()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

void UXMSStringVarGetterNode::OnSubNodeChanged(FName Identifier)
{
	Super::OnSubNodeChanged(Identifier);

	if (Identifier.IsEqual(GET_MEMBER_NAME_CHECKED(ThisClass, VariableName)))
	{
		if (UXMSVariableNameValueNode* VariableNameNode = VariableName.Get())
		{
			VariableNameNode->SetType(XMSValueType::String);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSStringValueInterface Interface
 */

bool UXMSStringVarGetterNode::GetString(FString& OutString)
{
	UXMSSpellExecutorComponent* SpellExecutor = UXMSNodeStaticLibrary::GetSpellExecutorComponent(GetOuter());
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
