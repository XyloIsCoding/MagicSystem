// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/XMSNode.h"
#include "Base/XMSNodeWithArray.h"
#include "Base/XMSNodeWithMap.h"

class UXMSNodeWithArray;
class UXMSNodeWithMap;
class UXMSNode;


template<typename Derived>
concept NodeClass = std::is_base_of_v<UXMSNode, Derived>;

template<typename Derived, typename BaseClass, typename BaseInterface>
concept DerivedNode = std::is_base_of_v<UXMSNode, Derived> && std::is_base_of_v<BaseClass, Derived> && std::is_base_of_v<BaseInterface, Derived>;




/**
 * Interface class for TXMSNodeContainer
 */
struct FXMSNodeContainer
{
	friend UXMSNodeWithMap;

	FXMSNodeContainer(UXMSNodeWithMap* Owner, const FString& Name)
	{
		// Register node container to SubNodes map of the owning node
		Owner->SubNodes.Add(Name, this);
	}
	virtual ~FXMSNodeContainer()
	{
	}

public:
	/** Checks if a class is compatible with this container */
	virtual bool IsCompatible(UClass* NodeClass) { return false; }
protected:
	virtual UXMSNode* GetGeneric() { return nullptr; }
	virtual void SetGeneric(UXMSNode* InNode) {}
};


/**
 * Wrapper for nodes with constrains over what nodes can be contained.
 * <p> Sub-nodes should always be wrapped by a TXMSNodeContainer since it allow them to be reflected
 * through UXMSNode::SubNodes </p>
 * 
 * @tparam BaseClass: subclass of UXMSNode that this container is allowed to hold.
 * @tparam BaseInterface: interface that the contained node must implement.
 */
template <NodeClass BaseClass, typename BaseInterface>
struct TXMSNodeContainer : public FXMSNodeContainer
{
	using CompatibilityCheck = TFunction<bool (UClass*)>;

	TXMSNodeContainer(UXMSNodeWithMap* Owner, const FString& Name, const CompatibilityCheck& Compatibility)
		: FXMSNodeContainer(Owner, Name)
		, CompatibilityCheckFunction(Compatibility)
		, Node(nullptr)
	{
	}

	virtual ~TXMSNodeContainer() override
	{
	}

	TXMSNodeContainer& operator=(const TXMSNodeContainer& Other) = delete;
	TXMSNodeContainer& operator=(TXMSNodeContainer&& Other) = delete;

	BaseInterface* Get()
	{
		return Cast<BaseInterface>(Node.Get());
	}

	template <DerivedNode<BaseClass, BaseInterface> NodeType>
	void Set(NodeType* InNode)
	{
		SetGeneric(static_cast<UXMSNode>(InNode));
	}

	/** Checks if a class is compatible with this container */
	virtual bool IsCompatible(UClass* NodeClass) override
	{
		if (!NodeClass->IsChildOf(BaseClass::StaticClass()))
		{
			return false;
		}

		if (!NodeClass->ImplementsInterface(BaseInterface::UClassType::StaticClass()))
		{
			return false;
		}

		if (!CompatibilityCheckFunction(NodeClass))
		{
			return false;
		}
		
		return true;
	}

protected:
	virtual UXMSNode* GetGeneric() override
	{
		return Node.Get();
	}
	
	virtual void SetGeneric(UXMSNode* InNode) override
	{
		if (InNode && IsCompatible(InNode->GetClass()))
		{
			Node.Reset(InNode);
		}
	}

private:
	CompatibilityCheck CompatibilityCheckFunction;
	TStrongObjectPtr<BaseClass> Node;
};




/**
 * Interface class for TXMSNodeContainer
 */
struct FXMSMultiNodeContainer
{
	friend UXMSNodeWithArray;

	FXMSMultiNodeContainer(UXMSNodeWithArray* Owner, const FString& Name)
	{
		// Register node container to SubNodes map of the owning node
		Owner->SubNodes = { Name, this };
	}
	virtual ~FXMSMultiNodeContainer()
	{
	}

public:
	/** Checks if a class is compatible with this container */
	virtual bool IsCompatible(UClass* NodeClass) { return false; }
protected:
	virtual UXMSNode* GetGeneric(int32 Index) { return nullptr; }
	virtual void SetGeneric(int32 Index, UXMSNode* InNode) {}
	virtual void AddGeneric(UXMSNode* InNode) {}
	virtual void InsertGeneric(int32 Index, UXMSNode* InNode) {}
	virtual void Remove(int32 Index) {}
};

/**
 * Wrapper for nodes with constrains over what nodes can be contained.
 * <p> Sub-nodes should always be wrapped by a TXMSMultiNodeContainer since it allow them to be reflected
 * through UXMSNode::SubNodes </p>
 * 
 * @tparam BaseClass: subclass of UXMSNode that this container is allowed to hold.
 * @tparam BaseInterface: interface that the contained node must implement.
 */
template <NodeClass BaseClass, typename BaseInterface>
struct TXMSMultiNodeContainer : public FXMSMultiNodeContainer
{
	using CompatibilityCheck = TFunction<bool (UClass*)>;

	TXMSMultiNodeContainer(UXMSNodeWithArray* Owner, const FString& Name, const CompatibilityCheck& Compatibility)
		: FXMSMultiNodeContainer(Owner, Name)
		, CompatibilityCheckFunction(Compatibility)
		, Nodes(nullptr)
	{
	}

	virtual ~TXMSMultiNodeContainer() override
	{
	}

	TXMSMultiNodeContainer& operator=(const TXMSMultiNodeContainer& Other) = delete;
	TXMSMultiNodeContainer& operator=(TXMSMultiNodeContainer&& Other) = delete;

	BaseInterface* Get(int32 Index)
	{
		if (!Nodes.IsValidIndex(Index)) return nullptr;
		return Cast<BaseInterface>(Nodes[Index].Get());
	}
	
	template <DerivedNode<BaseClass, BaseInterface> NodeType>
	void Set(int32 Index, NodeType* InNode)
	{
		if (!Nodes.IsValidIndex(Index)) return;
		SetGeneric(Index, static_cast<UXMSNode>(InNode));
	}

	template <DerivedNode<BaseClass, BaseInterface> NodeType>
	void Add(NodeType* InNode)
	{
		AddGeneric(InNode);
	}

	template <DerivedNode<BaseClass, BaseInterface> NodeType>
	void Insert(int32 Index, NodeType* InNode)
	{
		InsertGeneric(Index, InNode);
	}
	
	virtual void Remove(int32 Index) override
	{
		if (!Nodes.IsValidIndex(Index)) return;
		Nodes.RemoveAt(Index);
	}

	/** Checks if a class is compatible with this container */
	virtual bool IsCompatible(UClass* NodeClass) override
	{
		if (!NodeClass->IsChildOf(BaseClass::StaticClass()))
		{
			return false;
		}

		if (!NodeClass->ImplementsInterface(BaseInterface::UClassType::StaticClass()))
		{
			return false;
		}

		if (!CompatibilityCheckFunction(NodeClass))
		{
			return false;
		}
		
		return true;
	}

protected:
	virtual UXMSNode* GetGeneric(int32 Index) override
	{
		if (!Nodes.IsValidIndex(Index)) return nullptr;
		return Nodes[Index].Get();
	}
	
	virtual void SetGeneric(int32 Index, UXMSNode* InNode) override
	{
		if (!Nodes.IsValidIndex(Index)) return;
		if (InNode && IsCompatible(InNode->GetClass()))
		{
			Nodes[Index].Reset(InNode);
		}
	}

	virtual void AddGeneric(UXMSNode* InNode) override
	{
		if (InNode && IsCompatible(InNode->GetClass()))
		{
			Nodes.Add({InNode});
		}
	}
	
	virtual void InsertGeneric(int32 Index, UXMSNode* InNode) override
	{
		if (!Nodes.IsValidIndex(Index)) return;
		if (InNode && IsCompatible(InNode->GetClass()))
		{
			Nodes.Insert({InNode}, Index);
		}
	}

private:
	CompatibilityCheck CompatibilityCheckFunction;
	TArray<TStrongObjectPtr<BaseClass>> Nodes;
};

