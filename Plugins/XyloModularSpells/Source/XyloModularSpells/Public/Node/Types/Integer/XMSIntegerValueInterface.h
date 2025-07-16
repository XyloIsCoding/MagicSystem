// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSIntegerValueInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSIntegerValueInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSIntegerValueInterface
{
	GENERATED_BODY()

public:
	virtual bool GetInteger(int32& OutInteger) = 0;
};
