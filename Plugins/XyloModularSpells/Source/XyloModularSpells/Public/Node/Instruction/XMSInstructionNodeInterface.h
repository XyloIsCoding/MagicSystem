// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSInstructionNodeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSInstructionNodeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSInstructionNodeInterface
{
	GENERATED_BODY()

public:
	virtual void ExecuteNode() = 0;
};
