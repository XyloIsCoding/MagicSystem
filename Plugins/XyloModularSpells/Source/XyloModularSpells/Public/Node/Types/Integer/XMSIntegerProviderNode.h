// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Types/Integer/XMSIntegerValueInterface.h"
#include "Node/Types/String/XMSStringValueInterface.h"
#include "XMSIntegerProviderNode.generated.h"

/**
 * Provides type conversion from IntegerValue to other value types.
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSIntegerProviderNode : public UXMSNodeWithMap, public IXMSIntegerValueInterface, public IXMSStringValueInterface
{
	GENERATED_BODY()

public:
	UXMSIntegerProviderNode();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSIntegerValueInterface Interface
	 */
	
public:
	virtual int32 GetInteger() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSStringValueInterface Interface
	 */

public:
	virtual bool GetString(FString& OutString) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSIntegerProviderNode
	 */
	
public:
	TXMSNodeContainer<UXMSNode, IXMSIntegerValueInterface> IntegerNode = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, IntegerNode),
		[](UClass* NodeClass){ return true; } };
};
