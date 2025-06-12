// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeTypes.h"


class FXMSNodeRegistry
{
	
public:
	static void Load()
	{
		UE_LOG(LogTemp, Display, TEXT("Loading Node Registry"))
	}

private:
	template <typename NodeType>
	static TXMSNodeDefinition<NodeType> RegisterNode(FGameplayTag InNodeId, TFunction<NodeType ()> InFunction)
	{
		UE_LOG(LogTemp, Display, TEXT("Registering: %s"), *InNodeId.ToString())
		TXMSNodeDefinition<NodeType> Result = TXMSNodeDefinition(InNodeId, InFunction);
		Registry.Add(InNodeId, Result);
		return Result;
	}

public:
	static TMap<FGameplayTag, FXMSNodeDefinition> Registry;
	static TXMSNodeDefinition<XMSNode> TEST_NODE;
	static TXMSNodeDefinition<XMSNode> TEST_NODE2;
	static TXMSNodeDefinition<XMSNode> TEST_NODE3;
	static TXMSNodeDefinition<XMSNode> TEST_NODE4;
	
};