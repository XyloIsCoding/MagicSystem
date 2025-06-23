// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Value/XMSIntegerValueInterface.h"
#include "Node/Value/XMSStringValueInterface.h"
#include "Node/Value/XMSVariableNameNode.h"
#include "XMSIntegerVarGetterNode.generated.h"


/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSIntegerVarGetterNode : public UXMSNodeWithMap, public IXMSIntegerValueInterface
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNode Interface
	 */

protected:
	virtual void OnSubNodeChanged(const FName& Identifier) override;
	
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
	TXMSNodeContainer<UXMSVariableNameNode, IXMSStringValueInterface> VariableName = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, VariableName),
		[](UClass* NodeClass){ return true; } };
};
