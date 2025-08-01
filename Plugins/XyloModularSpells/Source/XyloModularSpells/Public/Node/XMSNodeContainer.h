// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/XMSNode.h"
#include "Base/XMSNodeWithArray.h"
#include "Base/XMSNodeWithMap.h"


template<typename Derived>
concept NodeClass = std::is_base_of_v<UXMSNode, Derived>;

template<typename Derived, typename BaseClass, typename BaseInterface>
concept DerivedNode = std::is_base_of_v<UXMSNode, Derived> && std::is_base_of_v<BaseClass, Derived> && std::is_base_of_v<BaseInterface, Derived>;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/**
 * Interface class for TXMSNodeContainer
 */
struct FXMSNodeContainer
{
	friend UXMSNodeWithMap;

	FXMSNodeContainer(UXMSNodeWithMap* InOwner, FName InIdentifier)
		: Identifier(InIdentifier)
		, Owner(InOwner)
	{
		// Register node container to SubNodes map of the owning node
		if (InOwner) InOwner->SubNodes.Add(Identifier, this);
	}
	virtual ~FXMSNodeContainer()
	{
	}

	FXMSNodeContainer& operator=(const FXMSNodeContainer& Other) = delete;
	FXMSNodeContainer& operator=(FXMSNodeContainer&& Other) = delete;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * FXMSNodeContainer
	 */
	
public:
	/** Checks if a class is compatible with this container */
	virtual bool IsCompatible(UClass* NodeClass) const { return false; }
	virtual UClass* GetInterfaceClass() const { return nullptr; }
	virtual UClass* GetBaseClass() const { return nullptr; }
protected:
	virtual UXMSNode* GetGeneric() const { return nullptr; }
	virtual void SetGeneric(UXMSNode* InNode) {}

/*--------------------------------------------------------------------------------------------------------------------*/
	// ContainerManagement

protected:
	virtual void NodeSet(UXMSNode* InNode, UXMSNode* OldNode);
private:
	FName Identifier;
	TWeakObjectPtr<UXMSNodeWithMap> Owner;

	// ~ContainerManagement
/*--------------------------------------------------------------------------------------------------------------------*/
	
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/**
 * Wrapper for nodes with constrains over what nodes can be contained.
 * <p> Sub-nodes should always be wrapped by a TXMSNodeContainer since it allow them to be reflected
 * through UXMSNodeWithMap::SubNodes </p>
 * 
 * @tparam BaseClass: subclass of UXMSNode that this container is allowed to hold.
 * @tparam BaseInterface: interface that the contained node must implement.
 */
template <NodeClass BaseClass, typename BaseInterface>
struct TXMSNodeContainer : public FXMSNodeContainer
{
	using CompatibilityCheck = TFunction<bool (UClass*)>;

	TXMSNodeContainer(UXMSNodeWithMap* Owner, FName Identifier, const CompatibilityCheck& Compatibility)
		: FXMSNodeContainer(Owner, Identifier)
		, CompatibilityCheckFunction(Compatibility)
		, Node(nullptr)
	{
	}

	virtual ~TXMSNodeContainer() override
	{
	}

	TXMSNodeContainer& operator=(const TXMSNodeContainer& Other) = delete;
	TXMSNodeContainer& operator=(TXMSNodeContainer&& Other) = delete;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * FXMSNodeContainer Interface
	 */
	
public:
	/** Checks if a class is compatible with this container */
	virtual bool IsCompatible(UClass* NodeClass) const override
	{
		if (!NodeClass) return false;
		
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

	virtual UClass* GetInterfaceClass() const override
	{
		return BaseInterface::UClassType::StaticClass();
	}

	virtual UClass* GetBaseClass() const override
	{
		return BaseClass::StaticClass();
	}
	
protected:
	virtual UXMSNode* GetGeneric() const override
	{
		return Node.Get();
	}
	
	virtual void SetGeneric(UXMSNode* InNode) override
	{
		if (!InNode || IsCompatible(InNode->GetClass()))
		{
			UXMSNode* OldNode = Node.Get();
			Node.Reset(Cast<BaseClass>(InNode));
			NodeSet(InNode, OldNode);
		}
	}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * TXMSNodeContainer
	 */
	
public:
	BaseInterface* GetInterface() const
	{
		return Cast<BaseInterface>(Node.Get());
	}

	BaseClass* Get() const
	{
		return Node.Get();
	}

	template <DerivedNode<BaseClass, BaseInterface> NodeType>
	void Set(NodeType* InNode)
	{
		if (!InNode || IsCompatible(InNode->GetClass()))
		{
			UXMSNode* OldNode = Node.Get();
			Node.Reset(InNode);
			NodeSet(static_cast<UXMSNode*>(InNode), OldNode);
		}
	}

private:
	CompatibilityCheck CompatibilityCheckFunction;
	TStrongObjectPtr<BaseClass> Node;
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/**
 * Interface class for TXMSMultiNodeContainer
 */
struct FXMSMultiNodeContainer
{
	friend UXMSNodeWithArray;

	FXMSMultiNodeContainer(UXMSNodeWithArray* InOwner, FName InIdentifier)
		: Identifier(InIdentifier)
		, Owner(InOwner)
	{
		// Register node container to SubNodes map of the owning node
		if (InOwner) InOwner->SubNodes = { Identifier, this };
	}
	virtual ~FXMSMultiNodeContainer()
	{
	}

	FXMSMultiNodeContainer& operator=(const FXMSMultiNodeContainer& Other) = delete;
	FXMSMultiNodeContainer& operator=(FXMSMultiNodeContainer&& Other) = delete;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * FXMSMultiNodeContainer
	 */
	
public:
	/** Checks if a class is compatible with this container */
	virtual bool IsCompatible(UClass* NodeClass) const { return false; }
	virtual UClass* GetInterfaceClass() const { return nullptr; }
	virtual UClass* GetBaseClass() const { return nullptr; }
protected:
	virtual UXMSNode* GetGeneric(int32 Index) const { return nullptr; }
	/** @return All stored nodes, even if nullptr */
	virtual void GetAllGeneric(TArray<UXMSNode*>& OutSubNodes) const {}
	virtual void SetGeneric(int32 Index, UXMSNode* InNode) {}
	virtual void AddGeneric(UXMSNode* InNode) {}
	virtual void InsertGeneric(int32 Index, UXMSNode* InNode) {}
	virtual void Remove(int32 Index) {}

/*--------------------------------------------------------------------------------------------------------------------*/
	// ContainerManagement

protected:
	virtual void NodeSet(UXMSNode* InNode, int32 Index, UXMSNode* OldNode);
	virtual void NodeAdded(UXMSNode* InNode, int32 Index);
	virtual void NodeRemoved(int32 Index, UXMSNode* OldNode);

	virtual void ShiftUpPathIndexes(int32 From) {}
	virtual void ShiftDownPathIndexes(int32 From) {}
	void ShiftPathIndex(UXMSNode* Node, int32 Amount);

private:
	FName Identifier;
	TWeakObjectPtr<UXMSNodeWithArray> Owner;

	// ~ContainerManagement
/*--------------------------------------------------------------------------------------------------------------------*/
	
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/**
 * Wrapper for array of nodes with constrains over what nodes can be contained.
 * <p> Sub-nodes should always be wrapped by a TXMSMultiNodeContainer since it allow them to be reflected
 * through UXMSNodeWithArray::SubNodes </p>
 * 
 * @tparam BaseClass: subclass of UXMSNode that this container is allowed to hold.
 * @tparam BaseInterface: interface that the contained node must implement.
 */
template <NodeClass BaseClass, typename BaseInterface>
struct TXMSMultiNodeContainer : public FXMSMultiNodeContainer
{
	using CompatibilityCheck = TFunction<bool (UClass*)>;

	TXMSMultiNodeContainer(UXMSNodeWithArray* Owner, FName Identifier, const CompatibilityCheck& Compatibility)
		: FXMSMultiNodeContainer(Owner, Identifier)
		, CompatibilityCheckFunction(Compatibility)
		, Nodes()
	{
	}

	virtual ~TXMSMultiNodeContainer() override
	{
	}

	TXMSMultiNodeContainer& operator=(const TXMSMultiNodeContainer& Other) = delete;
	TXMSMultiNodeContainer& operator=(TXMSMultiNodeContainer&& Other) = delete;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * FXMSMultiNodeContainer Interface
	 */

public:
	/** Checks if a class is compatible with this container */
	virtual bool IsCompatible(UClass* NodeClass) const override
	{
		if (!NodeClass) return false;
		
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

	virtual UClass* GetInterfaceClass() const override
	{
		return BaseInterface::UClassType::StaticClass();
	}

	virtual UClass* GetBaseClass() const override
	{
		return BaseClass::StaticClass();
	}

	virtual void Remove(int32 Index) override
	{
		if (!Nodes.IsValidIndex(Index)) return;

		UXMSNode* OldNode = Nodes[Index].Get();
		Nodes.RemoveAt(Index);
		NodeRemoved(Index, OldNode);
	}
	
protected:
	virtual UXMSNode* GetGeneric(int32 Index) const override
	{
		if (!Nodes.IsValidIndex(Index)) return nullptr;
		return Nodes[Index].Get();
	}

	virtual void GetAllGeneric(TArray<UXMSNode*>& OutSubNodes) const override
	{
		for (const TStrongObjectPtr<BaseClass>& Node : Nodes)
		{
			OutSubNodes.Add(Node.Get());
		}
	}
	
	virtual void SetGeneric(int32 Index, UXMSNode* InNode) override
	{
		if (!Nodes.IsValidIndex(Index)) return;
		if (!InNode || IsCompatible(InNode->GetClass()))
		{
			UXMSNode* OldNode = Nodes[Index].Get();
			Nodes[Index].Reset(Cast<BaseClass>(InNode));
			NodeSet(InNode, Index, OldNode);
		}
	}

	virtual void AddGeneric(UXMSNode* InNode) override
	{
		if (!InNode || IsCompatible(InNode->GetClass()))
		{
			int32 Index = Nodes.Add(TStrongObjectPtr<BaseClass>(Cast<BaseClass>(InNode)));
			NodeAdded(InNode, Index);
		}
	}
	
	virtual void InsertGeneric(int32 Index, UXMSNode* InNode) override
	{
		if (!Nodes.IsValidIndex(Index)) return;
		if (!InNode || IsCompatible(InNode->GetClass()))
		{
			Nodes.Insert(TStrongObjectPtr<BaseClass>(Cast<BaseClass>(InNode)), Index);
			NodeAdded(InNode, Index);
		}
	}

/*--------------------------------------------------------------------------------------------------------------------*/
	// ContainerManagement

protected:
	virtual void ShiftUpPathIndexes(int32 From) override
	{
		// A, B, C, D, E, F    <- Content
		// 0, 1, 2, 3, 4, 5    <- Array index
		// 0, 1, 2, 3, 4, 5	   <- Path.Index
		
		// A, B, C, X, D, E, F <- Inserted X in pos 3
		// 0, 1, 2, 3, 4, 5, 6 <- Array index after adding
		// 0, 1, 2, 3, 3, 4, 5 <- Path.Index after adding
		
		// 0, 1, 2, 3, 4, 5, 6 <- Path.Index after shift
		// -> from array pos > 3 we shift up by 1 the Path.index

		for (auto It = Nodes.CreateIterator(); It; ++It)
		{
			// Important: We use '>' (look at comment on top)
			if (It.GetIndex() > From)
			{
				if (UXMSNode* Node = It->Get())
				{
					ShiftPathIndex(Node, 1);
				}
			}
		}
	}

	virtual void ShiftDownPathIndexes(int32 From) override
	{
		// A, B, C, D, E, F    <- Content
		// 0, 1, 2, 3, 4, 5	   <- Array index
		// 0, 1, 2, 3, 4, 5	   <- Path.Index
		
		// A, B, D, E, F       <- removed C in pos 2
		// 0, 1, 2, 3, 4       <- Array index after removing
		// 0, 1, 3, 4, 5       <- Path.Index after removing
		
		// 0, 1, 2, 3, 4       <- Path.Index after shift
		// -> from array pos >= 2 we shift down by 1 the Path.index

		for (auto It = Nodes.CreateIterator(); It; ++It)
		{
			// Important: We use '>=' (look at comment on top)
			if (It.GetIndex() >= From)
			{
				if (UXMSNode* Node = It->Get())
				{
					ShiftPathIndex(Node, -1);
				}
			}
		}
	}

	// ~ContainerManagement
/*--------------------------------------------------------------------------------------------------------------------*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * TXMSMultiNodeContainer
	 */

public:
	BaseInterface* GetInterface(int32 Index) const
	{
		if (!Nodes.IsValidIndex(Index)) return nullptr;
		return Cast<BaseInterface>(Nodes[Index].Get());
	}

	BaseClass* Get(int32 Index) const
	{
		if (!Nodes.IsValidIndex(Index)) return nullptr;
		return Nodes[Index].Get();
	}

	/** @return All stored nodes, even if nullptr */
	void GetAll(TArray<BaseInterface*>& OutSubNodes) const
	{
		for (const TStrongObjectPtr<BaseClass>& Node : Nodes)
		{
			OutSubNodes.Add(Cast<BaseInterface>(Node.Get()));
		}
	}
	
	template <DerivedNode<BaseClass, BaseInterface> NodeType>
	void Set(int32 Index, NodeType* InNode)
	{
		if (!Nodes.IsValidIndex(Index)) return;
		if (!InNode || IsCompatible(InNode->GetClass()))
		{
			UXMSNode* OldNode = Nodes[Index].Get();
			Nodes[Index].Reset(InNode);
			NodeSet(static_cast<UXMSNode*>(InNode), Index, OldNode);
		}
	}

	template <DerivedNode<BaseClass, BaseInterface> NodeType>
	void Add(NodeType* InNode)
	{
		if (!InNode || IsCompatible(InNode->GetClass()))
		{
			int32 Index = Nodes.Add(TStrongObjectPtr<BaseClass>(InNode));
			NodeAdded(static_cast<UXMSNode*>(InNode), Index);
		}
	}

	template <DerivedNode<BaseClass, BaseInterface> NodeType>
	void Insert(int32 Index, NodeType* InNode)
	{
		if (!Nodes.IsValidIndex(Index)) return;
		if (!InNode || IsCompatible(InNode->GetClass()))
		{
			Nodes.Insert(TStrongObjectPtr<BaseClass>(InNode), Index);
			NodeAdded(static_cast<UXMSNode*>(InNode), Index);
		}
	}
	
private:
	CompatibilityCheck CompatibilityCheckFunction;
	TArray<TStrongObjectPtr<BaseClass>> Nodes;
};

