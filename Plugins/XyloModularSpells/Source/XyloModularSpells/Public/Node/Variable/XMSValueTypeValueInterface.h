// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSValueTypeValueInterface.generated.h"

struct FGameplayTag;

// This class does not need to be modified.
UINTERFACE()
class UXMSValueTypeValueInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSValueTypeValueInterface
{
	GENERATED_BODY()

public:
	virtual const FGameplayTag& GetValueType() = 0;
};
