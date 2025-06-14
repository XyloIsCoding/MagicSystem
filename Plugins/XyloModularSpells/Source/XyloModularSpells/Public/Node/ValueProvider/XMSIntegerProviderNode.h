// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSValueProviderNode.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Value/XMSIntegerValueInterface.h"
#include "Node/Value/XMSStringValueInterface.h"
#include "XMSIntegerProviderNode.generated.h"

/**
 * Provides type conversion from IntegerValue to other value types.
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSIntegerProviderNode : public UXMSValueProviderNode, public IXMSIntegerValueInterface, public IXMSStringValueInterface
{
	GENERATED_BODY()

public:
	UXMSIntegerProviderNode();

public:
	virtual int32 GetInteger() override;
	virtual FString GetString() override;
private:
	TXMSNodeContainer<UXMSNode, IXMSIntegerValueInterface> IntegerNode = { this, FString(TEXT("IntegerNode")),
		[](UClass* NodeClass){ return true; } };
};
