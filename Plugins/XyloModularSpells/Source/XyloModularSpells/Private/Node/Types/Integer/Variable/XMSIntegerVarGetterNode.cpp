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
			VariableNameNode->SetType(XMSValueType::Integer);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSIntegerValueInterface Interface
 */

bool UXMSIntegerVarGetterNode::GetInteger(int32& OutInteger)
{
	UXMSSpellExecutorComponent* SpellExecutor = UXMSNodeStaticLibrary::GetSpellExecutorComponent(GetOuter());
	if (!SpellExecutor) return false;

	IXMSStringValueInterface* VariableNameNode = VariableName.GetInterface();
	if (!VariableNameNode) return false;
	
	FString VariableNameString;
	if (!VariableNameNode->GetString(VariableNameString))
	{
		return false;
	}
	
	return SpellExecutor->GetIntegerValue(VariableNameString, OutInteger);
}
