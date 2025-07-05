// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Types/String/XMSStringValueInterface.h"
#include "XMSStringProviderNode.generated.h"

class UXMSStringValueNode;

/**
 * Provides type conversion from StringValue to other value types.
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSStringProviderNode : public UXMSNodeWithMap, public IXMSStringValueInterface
{
	GENERATED_BODY()

public:
	UXMSStringProviderNode();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSStringValueInterface Interface
	 */
	
public:
	virtual bool GetString(FString& OutString) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSStringProviderNode
	 */
	
public:
	TXMSNodeContainer<UXMSNode, IXMSStringValueInterface> StringNode = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, StringNode),
		[](UClass* NodeClass){ return true; } };
};
