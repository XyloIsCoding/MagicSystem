// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Integer/Variable/XMSIntegerVarGetterNode.h"

#include "XMSNodeStaticLibrary.h"
#include "XMSTypes.h"
#include "SpellExecutor/XMSSpellExecutorInterface.h"
#include "SpellEditor/XMSSpellEditorInterface.h"
#include "SpellExecutor/XMSSpellExecutorComponent.h"


UXMSIntegerVarGetterNode::UXMSIntegerVarGetterNode()
{
	VariableName.Set(NewObject<UXMSVariableNameValueNode>(GetOuter()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

void UXMSIntegerVarGetterNode::OnSubNodeChanged(FName Identifier)
{
	Super::OnSubNodeChanged(Identifier);

	if (Identifier.IsEqual(GET_MEMBER_NAME_CHECKED(ThisClass, VariableName)))
	{
		if (UXMSVariableNameValueNode* VariableNameNode = VariableName.Get())
		{
			VariableNameNode->SetType(XMSVariableType::Integer);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSIntegerValueInterface Interface
 */

int32 UXMSIntegerVarGetterNode::GetInteger()
{
	UXMSSpellExecutorComponent* SpellExecutor = UXMSNodeStaticLibrary::GetSpellExecutorComponent(GetOuter());
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
