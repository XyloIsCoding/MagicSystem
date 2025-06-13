// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSStringProviderInterface.h"
#include "XMSValueProviderNode.h"
#include "Node/XMSNodeContainer.h"
#include "XMSStringProviderNode.generated.h"

class UXMSStringValueNode;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSStringProviderNode : public UXMSValueProviderNode, public IXMSStringProviderInterface
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
