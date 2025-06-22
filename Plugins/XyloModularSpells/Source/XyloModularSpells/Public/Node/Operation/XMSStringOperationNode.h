// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Value/XMSStringValueInterface.h"
#include "String/XMSStringOperatorInterface.h"
#include "XMSStringOperationNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSStringOperationNode : public UXMSNodeWithMap, public IXMSStringValueInterface
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSStringValueInterface Interface
	 */

public:
	virtual bool GetString(FString& OutString) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSStringOperationNode
	 */
	
public:
	TXMSNodeContainer<UXMSNode, IXMSStringOperatorInterface> StringOperator = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, StringOperator),
		[](UClass* NodeClass){ return true; } };
};
