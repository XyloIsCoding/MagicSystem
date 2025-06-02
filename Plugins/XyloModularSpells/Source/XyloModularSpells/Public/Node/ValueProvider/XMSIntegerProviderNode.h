// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSIntegerProviderNodeInterface.h"
#include "XMSValueProviderNode.h"
#include "UObject/Object.h"
#include "XMSIntegerProviderNode.generated.h"

class UXMSValueNode;

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSIntegerProviderNode : public UXMSValueProviderNode, public IXMSIntegerProviderNodeInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetIntegerValue() const override;

protected:
	UPROPERTY(EditAnywhere, Instanced, meta = (MustImplement = "/Script/XyloModularSpells.XMSIntegerValueNodeInterface"))
	TObjectPtr<UXMSValueNode> IntegerNode;
};
