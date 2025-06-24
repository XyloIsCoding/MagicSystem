// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSTypes.h"
#include "Components/ActorComponent.h"
#include "Node/Runnable/Instruction/XMSVariableDeclarationNode.h"
#include "XMSSpellEditorComponent.generated.h"

USTRUCT()
struct FXMSScopedVariable
{
	GENERATED_BODY()

	FXMSScopedVariable()
		: Name(FString())
		, Type(0)
		, DeclarationNode(nullptr)
	{
		
	}

	FXMSScopedVariable(const FString& VariableName, int32 VariableType, UXMSVariableDeclarationNode* InDeclarationNode)
		: Name(VariableName)
		, Type(VariableType)
		, DeclarationNode(InDeclarationNode)
	{
		
	}
	
	UPROPERTY()
	FString Name;
	
	UPROPERTY()
	int32 Type;

	/** Pointer to the node that declared this variable */
	UPROPERTY()
	TWeakObjectPtr<UXMSVariableDeclarationNode> DeclarationNode;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class XYLOMODULARSPELLS_API UXMSSpellEditorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UXMSSpellEditorComponent();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UActorComponent Interface
	 */
	
protected:
	virtual void BeginPlay() override;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSSpellEditorComponent
	 */

/*--------------------------------------------------------------------------------------------------------------------*/

public:
	void RegisterOrUpdateVariable(UXMSVariableDeclarationNode* DeclarationNode, const FString& Name, int32 Type);
	void UpdateVariableType(UXMSVariableDeclarationNode* DeclarationNode, int32 Type);
	void UnRegisterVariable(UXMSVariableDeclarationNode* DeclarationNode);
	void GetVariablesNamesByType(int32 Type, const UXMSNode* RequestingNode, TArray<FString>& OutVariableNames) const;
protected:
	bool HasVariable(const FString& Name, int32 Type = XMSVariableType::EVT_None) const;
	bool HasVariable(UXMSVariableDeclarationNode* DeclarationNode) const;
	FXMSScopedVariable* GetVariable(UXMSVariableDeclarationNode* DeclarationNode);

/*--------------------------------------------------------------------------------------------------------------------*/

	
private:
	UPROPERTY()
	TArray<FXMSScopedVariable> ScopedVariables;
	
};
