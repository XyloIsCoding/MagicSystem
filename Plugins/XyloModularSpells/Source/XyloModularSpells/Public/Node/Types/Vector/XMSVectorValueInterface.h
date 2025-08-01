// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSVectorValueInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSVectorValueInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSVectorValueInterface
{
	GENERATED_BODY()

public:
	virtual bool GetVector(FVector& OutVector) = 0;
};
