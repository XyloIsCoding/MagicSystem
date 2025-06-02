// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSInstructionNode.h"
#include "XMSPrintInstructionNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSPrintInstructionNode : public UXMSInstructionNode
{
	GENERATED_BODY()

public:
	virtual void ExecuteNode() override;

protected:
	UPROPERTY(EditAnywhere, Instanced, meta = (MustImplement = "/Script/XyloModularSpells.XMSStringProviderNodeInterface"))
	TObjectPtr<UXMSNode> StringProviderNode;
};
