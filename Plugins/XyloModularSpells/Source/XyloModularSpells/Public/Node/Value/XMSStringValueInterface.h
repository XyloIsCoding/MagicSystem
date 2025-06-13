// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/Base/XMSNodeInterface.h"
#include "UObject/Interface.h"
#include "XMSStringValueInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UXMSStringValueInterface : public UXMSNodeInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class XYLOMODULARSPELLS_API IXMSStringValueInterface : public IXMSNodeInterface
{
	GENERATED_BODY()

public:
	virtual FString GetString() = 0;
};
