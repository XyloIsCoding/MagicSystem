// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSValueNode.h"
#include "Node/ValueProvider/XMSStringProviderNodeInterface.h"
#include "XMSStringValueNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSStringValueNode : public UXMSValueNode, public IXMSStringProviderNodeInterface
{
	GENERATED_BODY()

public:
	virtual FString GetStringValue() const override;

protected:
	UPROPERTY(EditAnywhere)
	FString NodeValue;
};
