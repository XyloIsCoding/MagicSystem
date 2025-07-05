// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSVariableSetterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSVariableSetterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSVariableSetterInterface
{
	GENERATED_BODY()

public:
	virtual bool SetVariable() = 0;
};
