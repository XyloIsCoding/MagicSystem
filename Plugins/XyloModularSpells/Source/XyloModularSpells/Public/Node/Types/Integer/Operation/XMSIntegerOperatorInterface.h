// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSIntegerOperatorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSIntegerOperatorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSIntegerOperatorInterface
{
	GENERATED_BODY()

public:
	virtual bool ApplyIntegerOperation(int32& OutResult) = 0;
};
