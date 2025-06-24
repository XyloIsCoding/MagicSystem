// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Runnable/Instruction/XMSPrintInstructionNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSRunnableNodeInterface Interface
 */

int32 UXMSPrintInstructionNode::ExecuteNode()
{
	IXMSStringValueInterface* StringValueInterface = OutputString.GetInterface();
	if (!StringValueInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpellOutput >> ERROR: No string to print"))
		return 0;
	}
	
	FString OutputString;
	if (!StringValueInterface->GetString(OutputString))
	{
		UE_LOG(LogTemp, Warning, TEXT("SpellOutput >> ERROR: Unable to find string"))
		return 0;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("SpellOutput >> %s"), *OutputString)
	return 1;
}
