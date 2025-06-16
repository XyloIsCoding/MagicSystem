// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSIntegerValueInterface.h"
#include "Node/Base/XMSNodeWithValue.h"
#include "XMSIntegerValueNode.generated.h"

/**
 * Contains a raw integer value.
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSIntegerValueNode : public UXMSNodeWithValue, public IXMSIntegerValueInterface
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSIntegerValueInterface Interface
	 */
	
public:
	virtual int32 GetInteger() override { return Integer; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSIntegerValueNode
	 */

public:
	virtual void SetInteger(int32 InInteger);
private:
	int32 Integer = 0;
};
