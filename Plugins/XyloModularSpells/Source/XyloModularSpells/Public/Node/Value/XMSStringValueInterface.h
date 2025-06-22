// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSStringValueInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSStringValueInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSStringValueInterface
{
	GENERATED_BODY()

public:
	virtual bool GetString(FString& OutString) = 0;
};
