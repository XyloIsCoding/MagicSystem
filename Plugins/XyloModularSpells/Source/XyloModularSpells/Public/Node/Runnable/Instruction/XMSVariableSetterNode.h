// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Base/XMSNodeWithMap.h"
#include "Node/Runnable/XMSRunnableNodeInterface.h"
#include "XMSVariableSetterNode.generated.h"

class IXMSVariableSetterInterface;
/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSVariableSetterNode : public UXMSNodeWithMap, public  IXMSRunnableNodeInterface
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSRunnableNodeInterface Interface
	 */

public:
	virtual int32 ExecuteNode() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSCreateVariableNode
	 */
	
public:
	TXMSNodeContainer<UXMSNode, IXMSVariableSetterInterface> Setter = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, Setter),
		[](UClass* NodeClass){ return true; } };
};
