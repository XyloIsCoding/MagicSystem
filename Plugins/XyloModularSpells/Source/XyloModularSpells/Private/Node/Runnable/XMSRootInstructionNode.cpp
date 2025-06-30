// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Runnable/XMSRootInstructionNode.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSRunnableNodeInterface Interface
 */

int32 UXMSRootInstructionNode::ExecuteNode()
{
	if (IXMSRunnableNodeInterface* RunnableNode = Instruction.GetInterface())
	{
		return RunnableNode->ExecuteNode();
	}
	return 0;
}
