// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSTypes.h"
#include "Components/ActorComponent.h"
#include "Node/Runnable/Instruction/XMSVariableDeclarationNode.h"
#include "XMSSpellEditorComponent.generated.h"

class UXMSNodeOptionsSelectionWidget;
class UXMSNodeCanvasWidget;
class UXMSNodeContainerWidget;

USTRUCT()
struct FXMSScopedVariable
{
	GENERATED_BODY()

	FXMSScopedVariable()
		: Name(FString())
		, Type(XMSVariableType::None)
		, DeclarationNode(nullptr)
	{
		
	}

	FXMSScopedVariable(const FString& VariableName, const FGameplayTag& VariableType, UXMSVariableDeclarationNode* InDeclarationNode)
		: Name(VariableName)
		, Type(VariableType)
		, DeclarationNode(InDeclarationNode)
	{
		
	}
	
	UPROPERTY()
	FString Name;
	
	UPROPERTY()
	FGameplayTag Type;

	/** Pointer to the node that declared this variable */
	UPROPERTY()
	TWeakObjectPtr<UXMSVariableDeclarationNode> DeclarationNode;
};

DECLARE_MULTICAST_DELEGATE_FourParams(FXMSDeclaredVariableListChangedSignature, const FString& /* NeVariableName */, const FGameplayTag& /* NeVariableType */, const FString& /* OldVariableName */, const FGameplayTag& /* OldVariableType */)

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
	// VariablesManagement
	
public:
	/** Broadcasts the Name and Type of the changed variable */
	FXMSDeclaredVariableListChangedSignature DeclaredVariableListChangedDelegate;
	void RegisterOrUpdateVariable(UXMSVariableDeclarationNode* DeclarationNode, const FString& NewName, const FGameplayTag& NewType);
	void UpdateVariableType(UXMSVariableDeclarationNode* DeclarationNode, const FGameplayTag& Type);
	void UnRegisterVariable(UXMSVariableDeclarationNode* DeclarationNode);
	void GetVariablesNamesByType(const UXMSNode* RequestingNode, const FGameplayTag& Type, TArray<FString>& OutVariableNames) const;
protected:
	bool HasVariableInScope(UXMSNode* RequestingNode, const FString& Name, const FGameplayTag& Type = XMSVariableType::None) const;
	bool HasVariable(UXMSVariableDeclarationNode* DeclarationNode) const;
	FXMSScopedVariable* GetVariable(UXMSVariableDeclarationNode* DeclarationNode);
private:
	UPROPERTY()
	TArray<FXMSScopedVariable> ScopedVariables;

	// ~VariablesManagement
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// NodeCanvas
	
public:
	UXMSNodeCanvasWidget* CreateNodeCanvas(APlayerController* PlayerController, UXMSNode* RootNode);

	// ~NodeCanvas
/*--------------------------------------------------------------------------------------------------------------------*/
	
};
