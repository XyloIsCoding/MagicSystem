// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/Integer/Variable/XMSIntegerVarSetterNode.h"

#include "XMSNodeStaticLibrary.h"
#include "XMSTypes.h"
#include "SpellExecutor/XMSSpellExecutorInterface.h"
#include "SpellEditor/XMSSpellEditorInterface.h"
#include "SpellExecutor/XMSSpellExecutorComponent.h"


UXMSIntegerVarSetterNode::UXMSIntegerVarSetterNode()
{
	VariableName.Set(NewObject<UXMSVariableNameValueNode>(GetOuter()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

void UXMSIntegerVarSetterNode::OnSubNodeChanged(FName Identifier)
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
 * IXMSVariableSetterInterface Interface
 */

bool UXMSIntegerVarSetterNode::SetVariable()
{
	UXMSSpellExecutorComponent* SpellExecutor = UXMSNodeStaticLibrary::GetSpellExecutorComponent(GetOuter());
	if (!SpellExecutor) return false;

	IXMSStringValueInterface* VariableNameNode = VariableName.GetInterface();
	if (!VariableNameNode) return false;

	IXMSIntegerValueInterface* Value = IntegerValue.GetInterface();
	if (!Value) return false;
	
	FString VariableNameString;
	if (!VariableNameNode->GetString(VariableNameString)) return false;
	if (VariableNameString.IsEmpty()) return false;

	int32 IntegerValue = 0;
	Value->GetInteger(IntegerValue);
	SpellExecutor->SetIntegerValue(VariableNameString, IntegerValue);
	return true;
}
