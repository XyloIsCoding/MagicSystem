// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSFloatOperatorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSFloatOperatorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSFloatOperatorInterface
{
	GENERATED_BODY()

public:
	virtual bool ApplyFloatOperation(float& OutResult) = 0;
};
