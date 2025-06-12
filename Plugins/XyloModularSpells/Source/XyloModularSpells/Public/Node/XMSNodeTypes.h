// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "XMSNode.h"

class XMSNode;

template<typename Derived, typename BaseClass, typename BaseInterface>
concept DerivedNode = std::is_base_of_v<BaseClass, Derived> && std::is_base_of_v<BaseInterface, Derived>;

/**
 * Class used as entry for NodeRegistry. Links a GameplayTag to a builder function.
 * It has protected constructor, since the templated version should be used to create this class
 */
class FXMSNodeDefinition
{

protected:
	FXMSNodeDefinition(FGameplayTag InNodeId)
		: NodeId(InNodeId)
	{
		
	}

public:
	virtual ~FXMSNodeDefinition()
	{
		
	}
	
public:
	FGameplayTag GetNodeId() const { return NodeId; }
	virtual XMSNode CreateNode() const { return XMSNode(); } //TODO: we want to return a ptr
	
private:
	FGameplayTag NodeId;
	
};

/**
 * Templated version of FXMSNodeDefinition
 */
template <typename NodeType>
class TXMSNodeDefinition : public FXMSNodeDefinition
{

public:
	TXMSNodeDefinition(FGameplayTag InNodeId, TFunction<NodeType ()> InFunction)
		: FXMSNodeDefinition(InNodeId)
		, NodeBuilder(InFunction)
	{
		
	}

	virtual XMSNode CreateNode() const override
	{
		return NodeBuilder(); // TODO: fix cause we want to give ownership of the object to the caller
	}

private:
	TFunction<NodeType ()> NodeBuilder;
};

