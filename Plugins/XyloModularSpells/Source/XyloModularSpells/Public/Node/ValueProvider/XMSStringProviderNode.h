// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSStringProviderNodeInterface.h"
#include "Node/XMSNode.h"
#include "UObject/Object.h"
#include "XMSStringProviderNode.generated.h"

class UXMSValueNode;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSStringProviderNode : public UXMSNode, public IXMSStringProviderNodeInterface
{
	GENERATED_BODY()

public:
	virtual FString GetStringValue() const override;

protected:
	UPROPERTY(EditAnywhere, Instanced, meta = (MustImplement = "/Script/XyloModularSpells.XMSStringValueNodeInterface"))
	TObjectPtr<UXMSValueNode> StringNode;
};
