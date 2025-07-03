// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSVariableSetterInterface.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Value/XMSStringValueInterface.h"
#include "Node/Value/XMSVariableNameNode.h"
#include "XMSStringVarSetterNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSStringVarSetterNode : public UXMSNodeWithMap, public IXMSVariableSetterInterface
{
	GENERATED_BODY()

public:
	UXMSStringVarSetterNode();

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
	 * UXMSStringVarSetterNode
	 */
	
public:
	TXMSNodeContainer<UXMSVariableNameNode, IXMSStringValueInterface> VariableName = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, VariableName),
		[](UClass* NodeClass){ return true; } };

	TXMSNodeContainer<UXMSNode, IXMSStringValueInterface> StringValue = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, StringValue),
		[](UClass* NodeClass){ return true; } };
};
