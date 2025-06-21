// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSRunnableNodeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSRunnableNodeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSRunnableNodeInterface
{
	GENERATED_BODY()

public:
	virtual int32 ExecuteNode() = 0;
};
