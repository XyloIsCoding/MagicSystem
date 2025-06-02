// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSIntegerValueNodeInterface.h"
#include "XMSStringValueNodeInterface.h"
#include "XMSValueNode.h"
#include "XMSIntegerValueNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSIntegerValueNode : public UXMSValueNode, public IXMSIntegerValueNodeInterface, public IXMSStringValueNodeInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetIntegerValue() const override;
	virtual FString GetStringValue() const override;

protected:
	UPROPERTY(EditAnywhere)
	int32 NodeValue;
};
