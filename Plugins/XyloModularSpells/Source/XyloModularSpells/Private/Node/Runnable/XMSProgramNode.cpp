// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Runnable/XMSProgramNode.h"

UXMSProgramNode::UXMSProgramNode()
{
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSRunnableNodeInterface Interface
 */

int32 UXMSProgramNode::ExecuteNode()
{
	TArray<IXMSRunnableNodeInterface*> InstructionsArray;
	Instructions.GetAll(InstructionsArray);
	for (IXMSRunnableNodeInterface* RunnableNodeInterface : InstructionsArray)
	{
		if (RunnableNodeInterface)
		{
			RunnableNodeInterface->ExecuteNode();
		}
	}
	return 0;
}
