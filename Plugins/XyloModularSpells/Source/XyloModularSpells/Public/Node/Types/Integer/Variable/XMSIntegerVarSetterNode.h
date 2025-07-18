// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/Variable/XMSVariableSetterInterface.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Types/Integer/XMSIntegerValueInterface.h"
#include "Node/Types/String/XMSStringValueInterface.h"
#include "Node/Variable/XMSVariableNameValueNode.h"
#include "XMSIntegerVarSetterNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSIntegerVarSetterNode : public UXMSNodeWithMap, public IXMSVariableSetterInterface
{
	GENERATED_BODY()

public:
	UXMSIntegerVarSetterNode();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNode Interface
	 */

protected:
	virtual void OnSubNodeChanged(FName Identifier) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSVariableSetterInterface Interface
	 */

public:
	virtual bool SetVariable() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSIntegerVarSetterNode
	 */
	
public:
	TXMSNodeContainer<UXMSVariableNameValueNode, IXMSStringValueInterface> VariableName = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, VariableName),
		[](UClass* NodeClass){ return true; } };

	TXMSNodeContainer<UXMSNode, IXMSIntegerValueInterface> IntegerValue = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, IntegerValue),
		[](UClass* NodeClass){ return true; } };
};
