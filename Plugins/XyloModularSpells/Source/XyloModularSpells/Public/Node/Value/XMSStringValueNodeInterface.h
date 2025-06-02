// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSStringValueNodeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSStringValueNodeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSStringValueNodeInterface
{
	GENERATED_BODY()

public:
	virtual FString GetStringValue() const = 0;
	
};
