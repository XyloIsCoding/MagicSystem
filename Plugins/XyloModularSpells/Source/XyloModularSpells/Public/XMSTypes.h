// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSTypes.generated.h"

DECLARE_DELEGATE_OneParam()

USTRUCT()
struct FXMSMyStruct
{
	GENERATED_BODY()
	
};

template<typename Derived, typename BaseClass, typename BaseInterface>
concept Derived = std::is_base_of<BaseClass, Derived>::value && std::is_base_of<BaseInterface, Derived>::value;
 
template<typename T, typename Interface>
class TXMSNode 
{
	template <Derived<T, Interface> A> 
	TXMSNode& operator=(A* SourceObject)
	{
		*this = TXMSNode(SourceObject);
		return *this;
	}
	
public:
	TObjectPtr<T> Node;
};

template <typename T, typename Interface>
struct TCallTraits<TXMSNode<T, Interface>> : public TCallTraitsBase<TXMSNode<T, Interface>>
{
	using ConstPointerType = TXMSNode<T, Interface>;
};