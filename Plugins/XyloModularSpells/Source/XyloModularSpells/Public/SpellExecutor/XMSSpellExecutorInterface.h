// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSSpellExecutorInterface.generated.h"

class UXMSSpellExecutorComponent;

// This class does not need to be modified.
UINTERFACE()
class UXMSSpellExecutorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSSpellExecutorInterface
{
	GENERATED_BODY()

public:
	virtual UXMSSpellExecutorComponent* GetSpellExecutorComponent() = 0;
};
