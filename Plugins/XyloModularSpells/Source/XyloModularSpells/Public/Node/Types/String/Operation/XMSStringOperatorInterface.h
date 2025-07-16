// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "XMSStringOperatorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSStringOperatorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSStringOperatorInterface
{
	GENERATED_BODY()

public:
	virtual bool ApplyStringOperation(FString& OutResult) = 0;
};
