// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/XMSNode.h"

class IXMSNodeInterface;
class UXMSNode;


template<typename Derived>
concept NodeClass = std::is_base_of_v<UXMSNode, Derived>;

template<typename Derived>
concept NodeInterface = std::is_base_of_v<IXMSNodeInterface, Derived>;

template<typename Derived, typename BaseClass, typename BaseInterface>
concept DerivedNode = std::is_base_of_v<UXMSNode, Derived> && std::is_base_of_v<BaseClass, Derived> && std::is_base_of_v<BaseInterface, Derived>;


struct FXMSNodeContainer
{
	friend UXMSNode;

	FXMSNodeContainer(UXMSNode* Owner, const FString& Name)
	{
		Owner->SubNodes.Add(Name, this);
	}
	virtual ~FXMSNodeContainer()
	{
		
	}

public:
	virtual bool IsCompatible(UClass* NodeClass) { return false; }
protected:
	virtual UXMSNode* GetGeneric() { return nullptr; }
	virtual void SetGeneric(UXMSNode* InNode) {}
};


template <NodeClass BaseClass, typename BaseInterface>
struct TXMSNodeContainer : public FXMSNodeContainer
{
	using CompatibilityCheck = TFunction<bool (UClass*)>;

	TXMSNodeContainer(UXMSNode* Owner, const FString& Name, const CompatibilityCheck& Compatibility)
		: FXMSNodeContainer(Owner, Name)
		, CompatibilityCheckFunction(Compatibility)
		, Node(nullptr)
	{
		
	}

	virtual ~TXMSNodeContainer() override
	{
		//UE_LOG(LogTemp, Error, TEXT("TXMSNodeContainer getting deleted"))
	}

	TXMSNodeContainer& operator=(const TXMSNodeContainer& Other) = delete;
	TXMSNodeContainer& operator=(TXMSNodeContainer&& Other) = delete;

	BaseInterface* Get()
	{
		if (BaseClass* NodePtr = Node.Get())
		{
			UE_LOG(LogTemp, Warning, TEXT("TXMSNodeContainer::Get >> %s"), *NodePtr->GetName())
		}
		return Cast<BaseInterface>(Node.Get());
	}

	template <DerivedNode<BaseClass, BaseInterface> NodeType>
	void Set(NodeType* InNode)
	{
		SetGeneric(static_cast<UXMSNode>(InNode));
	}

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
		if (BaseClass* NodePtr = Node.Get())
		{
			UE_LOG(LogTemp, Warning, TEXT("TXMSNodeContainer::GetGeneric >> %s"), *NodePtr->GetName())
		}
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
