// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSIntegerValueNodeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSIntegerValueNodeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSIntegerValueNodeInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetIntegerValue() const = 0;
	
};
