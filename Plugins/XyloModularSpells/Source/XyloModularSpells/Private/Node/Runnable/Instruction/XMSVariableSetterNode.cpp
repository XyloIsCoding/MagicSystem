// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Runnable/Instruction/XMSVariableSetterNode.h"

#include "Node/Variable/Setter/XMSVariableSetterInterface.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSRunnableNodeInterface Interface
 */

int32 UXMSVariableSetterNode::ExecuteNode()
{
	IXMSVariableSetterInterface* VariableSetter = Setter.Get();
	if (!VariableSetter) return 0;

	if (VariableSetter->SetVariable()) return 1;
	return 0;
}
