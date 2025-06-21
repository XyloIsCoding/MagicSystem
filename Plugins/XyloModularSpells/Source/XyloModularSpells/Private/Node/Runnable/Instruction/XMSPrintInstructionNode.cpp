// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Runnable/Instruction/XMSPrintInstructionNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSRunnableNodeInterface Interface
 */

int32 UXMSPrintInstructionNode::ExecuteNode()
{
	IXMSStringValueInterface* StringValueInterface = OutputString.Get();
	if (!StringValueInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpellOutput >> ERROR: No string to print"))
		return 0;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("SpellOutput >> %s"), *StringValueInterface->GetString())
	return 1;
}
