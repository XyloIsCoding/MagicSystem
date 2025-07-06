// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSVariableTypeValueInterface.generated.h"

struct FGameplayTag;

// This class does not need to be modified.
UINTERFACE()
class UXMSVariableTypeValueInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSVariableTypeValueInterface
{
	GENERATED_BODY()

public:
	virtual const FGameplayTag& GetVariableType() = 0;
};
