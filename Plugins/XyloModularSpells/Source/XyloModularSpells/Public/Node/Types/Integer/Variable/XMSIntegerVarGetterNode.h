// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Types/Integer/XMSIntegerValueInterface.h"
#include "Node/Types/String/XMSStringValueInterface.h"
#include "Node/Variable/XMSVariableNameValueNode.h"
#include "XMSIntegerVarGetterNode.generated.h"


/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSIntegerVarGetterNode : public UXMSNodeWithMap, public IXMSIntegerValueInterface
{
	GENERATED_BODY()

public:
	UXMSIntegerVarGetterNode();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNode Interface
	 */

protected:
	virtual void OnSubNodeChanged(FName Identifier) override;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSIntegerValueInterface Interface
	 */
	
public:
	virtual int32 GetInteger() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSIntegerVarGetterNode
	 */
	
public:
	TXMSNodeContainer<UXMSVariableNameValueNode, IXMSStringValueInterface> VariableName = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, VariableName),
		[](UClass* NodeClass){ return true; } };
};
