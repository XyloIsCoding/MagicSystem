// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSIntegerValueInterface.h"
#include "XMSStringValueInterface.h"
#include "XMSValueNode.h"
#include "XMSIntegerValueNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSIntegerValueNode : public UXMSValueNode, public IXMSIntegerValueInterface, public IXMSStringValueInterface
{
	GENERATED_BODY()

public:
	virtual void SetInteger(int32 InInteger);
	virtual int32 GetInteger() override { return Integer; }
	virtual FString GetString() override { return FString::FromInt(Integer); }
private:
	int32 Integer = 0;
};
