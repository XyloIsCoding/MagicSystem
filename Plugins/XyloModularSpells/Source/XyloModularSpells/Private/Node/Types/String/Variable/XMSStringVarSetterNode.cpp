// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Types/String/Variable/XMSStringVarSetterNode.h"

#include "XMSNodeStaticLibrary.h"
#include "XMSTypes.h"
#include "SpellExecutor/XMSSpellExecutorInterface.h"
#include "SpellEditor/XMSSpellEditorInterface.h"
#include "SpellExecutor/XMSSpellExecutorComponent.h"


UXMSStringVarSetterNode::UXMSStringVarSetterNode()
{
	VariableName.Set(NewObject<UXMSVariableNameValueNode>(GetOuter()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNode Interface
 */

void UXMSStringVarSetterNode::OnSubNodeChanged(FName Identifier)
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
 * IXMSVariableSetterInterface Interface
 */

bool UXMSStringVarSetterNode::SetVariable()
{
	UXMSSpellExecutorComponent* SpellExecutor = UXMSNodeStaticLibrary::GetSpellExecutorComponent(GetOuter());
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
