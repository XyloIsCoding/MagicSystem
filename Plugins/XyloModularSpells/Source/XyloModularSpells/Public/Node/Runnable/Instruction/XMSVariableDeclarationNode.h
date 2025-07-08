// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/XMSNodeContainer.h"
#include "Node/Runnable/XMSRunnableNodeInterface.h"
#include "Node/Types/String/XMSStringValueInterface.h"
#include "Node/Types/String/XMSStringValueNode.h"
#include "Node/Variable/XMSValueTypeValueInterface.h"
#include "Node/Variable/XMSValueTypeValueNode.h"
#include "XMSVariableDeclarationNode.generated.h"

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSVariableDeclarationNode : public UXMSNodeWithMap, public  IXMSRunnableNodeInterface
{
	GENERATED_BODY()

public:
	UXMSVariableDeclarationNode();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNode Interface
	 */

public:
	virtual void PreRemovedFromParent() override;
	virtual void OnSubNodeChanged(FName Identifier) override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * IXMSRunnableNodeInterface Interface
	 */

public:
	virtual int32 ExecuteNode() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSVariableDeclarationNode
	 */

public:
	virtual void OnVariableTypeChanged(const FGameplayTag& NewType, const FGameplayTag& OldType);
	virtual void OnVariableNameChanged(const FString& NewName, const FString& OldName);
	
public:
	TXMSNodeContainer<UXMSValueTypeValueNode, IXMSValueTypeValueInterface> VariableType = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, VariableType),
		[](UClass* NodeClass){ return true; } };

	TXMSNodeContainer<UXMSStringValueNode, IXMSStringValueInterface> VariableName = {
		this,
		GET_MEMBER_NAME_CHECKED(ThisClass, VariableName),
		[](UClass* NodeClass){ return true; } };
};
