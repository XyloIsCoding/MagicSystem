// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSValueNode.h"
#include "Node/ValueProvider/XMSStringProviderInterface.h"
#include "XMSStringValueNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSStringValueNode : public UXMSValueNode, public IXMSStringProviderInterface
{
	GENERATED_BODY()

public:
	virtual void SetString(const FString& InString);
	virtual FString GetString() override { return String; }
private:
	UPROPERTY()
	FString String = FString(TEXT("DefaultText"));
};
