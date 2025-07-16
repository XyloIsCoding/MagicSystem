// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSRotatorValueInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSRotatorValueInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSRotatorValueInterface
{
	GENERATED_BODY()

public:
	virtual bool GetRotator(FRotator& OutRotator) = 0;
};
