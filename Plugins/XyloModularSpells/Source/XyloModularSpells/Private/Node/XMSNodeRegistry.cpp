// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/XMSNodeRegistry.h"

#include "Node/XMSNode.h"
#include "Node/XMSNodeIdentifierTags.h"

TMap<FGameplayTag, FXMSNodeDefinition> FXMSNodeRegistry::Registry = TMap<FGameplayTag, FXMSNodeDefinition>();
TXMSNodeDefinition<XMSNode> FXMSNodeRegistry::TEST_NODE = RegisterNode<XMSNode>(TAG_XMS_NodeIdentifier_Node, [](){ return XMSNode(); });
TXMSNodeDefinition<XMSNode> FXMSNodeRegistry::TEST_NODE2 = RegisterNode<XMSNode>(TAG_XMS_NodeIdentifier_InstructionNode, [](){ return XMSNode(); });
TXMSNodeDefinition<XMSNode> FXMSNodeRegistry::TEST_NODE3 = RegisterNode<XMSNode>(TAG_XMS_NodeIdentifier_StringProvider, [](){ return XMSNode(); });
TXMSNodeDefinition<XMSNode> FXMSNodeRegistry::TEST_NODE4 = RegisterNode<XMSNode>(TAG_XMS_NodeIdentifier_IntegerProvider, [](){ return XMSNode(); });
