// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/Instruction/XMSPrintInstructionNode.h"

#include "Node/ValueProvider/XMSStringProviderNodeInterface.h"

void UXMSPrintInstructionNode::ExecuteNode()
{
	if (IsValid(StringProviderNode))
	{
		if (IXMSStringProviderNodeInterface* StringProviderInterface = Cast<IXMSStringProviderNodeInterface>(StringProviderNode))
		{
			UE_LOG(LogTemp, Warning, TEXT(">> %s"), *StringProviderInterface->GetStringValue())
		}
	}
}
