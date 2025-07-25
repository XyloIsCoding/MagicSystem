// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Types/String/XMSStringValueInterface.h"
#include "Node/Variable/XMSVariableNameValueNode.h"
#include "XMSStringVarGetterNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSStringVarGetterNode : public UXMSNodeWithMap, public IXMSStringValueInterface
{
	GENERATED_BODY()

public:
	UXMSStringVarGetterNode();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNode Interface
	 */

protected:
	virtual void OnSubNodeChanged(FName Identifier) override;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSStringValueInterface Interface
	 */
	
public:
	virtual bool GetString(FString& OutString) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSStringVarGetterNode
	 */
	
public:
	TXMSNodeContainer<UXMSVariableNameValueNode, IXMSStringValueInterface> VariableName = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, VariableName),
		[](UClass* NodeClass){ return true; } };
};
