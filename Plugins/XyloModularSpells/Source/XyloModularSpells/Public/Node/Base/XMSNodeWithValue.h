// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNode.h"
#include "XMSNodeWithValue.generated.h"

/**
 * Value Nodes contain a raw value of their type, and should only implement the interface for their value!
 */
UCLASS(Abstract)
class XYLOMODULARSPELLS_API UXMSNodeWithValue : public UXMSNode
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNode Interface
	 */
	
public:
	virtual TSharedPtr<FJsonObject> SerializeToJson(bool& bOutSuccess) override;
	virtual void DeserializeFromJson(TSharedPtr<FJsonObject>) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeWithValue Interface
	 */

protected:
	static const FString ValueJsonKey;
	
	// TODO: Do some trick to store a void ptr to the value and cast it to right class or something
	
};
