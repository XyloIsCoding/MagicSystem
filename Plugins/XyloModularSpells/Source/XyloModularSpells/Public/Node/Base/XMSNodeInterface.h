// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSNodeInterface.generated.h"

class UXMSNode;


// This class does not need to be modified.
UINTERFACE()
class UXMSNodeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSNodeInterface
{
	GENERATED_BODY()

public:
	virtual UXMSNode* GetSubNode(const FString& SubNodeName) = 0;
	virtual void SetSubNode(const FString& SubNodeName, UXMSNode* InNode) = 0;
};
