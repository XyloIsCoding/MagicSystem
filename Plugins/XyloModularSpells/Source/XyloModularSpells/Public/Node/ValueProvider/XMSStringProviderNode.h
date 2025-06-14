// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSValueProviderNode.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Value/XMSStringValueInterface.h"
#include "XMSStringProviderNode.generated.h"

class UXMSStringValueNode;

/**
 * Provides type conversion from StringValue to other value types.
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSStringProviderNode : public UXMSValueProviderNode, public IXMSStringValueInterface
{
	GENERATED_BODY()

public:
	UXMSStringProviderNode();

public:
	virtual FString GetString() override;
private:
	TXMSNodeContainer<UXMSNode, IXMSStringValueInterface> StringNode = { this, FString(TEXT("StringNode")),
		[](UClass* NodeClass){ return true; } };
};
