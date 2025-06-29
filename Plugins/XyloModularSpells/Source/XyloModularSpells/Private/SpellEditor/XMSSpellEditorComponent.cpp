// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellEditor/XMSSpellEditorComponent.h"

#include "XMSModularSpellsSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Node/XMSNodeDataRegistry.h"
#include "UI/XMSNodeCanvasWidget.h"
#include "UI/XMSNodeClassOptionsWidget.h"
#include "UI/SubNode/XMSArraySubNodeWidget.h"
#include "UI/SubNode/XMSMapSubNodeWidget.h"
#include "UI/SubNode/XMSNodeValueWidget.h"


UXMSSpellEditorComponent::UXMSSpellEditorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UActorComponent Interface
 */

void UXMSSpellEditorComponent::BeginPlay()
{
	Super::BeginPlay();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSSpellEditorComponent
 */

/*--------------------------------------------------------------------------------------------------------------------*/

void UXMSSpellEditorComponent::RegisterOrUpdateVariable(UXMSVariableDeclarationNode* DeclarationNode, const FString& Name, int32 Type)
{
	if (Name.IsEmpty()) return;
	
	FXMSScopedVariable* ScopedVariable = GetVariable(DeclarationNode);
	if (!ScopedVariable)
	{
		if (!HasVariableInScope(DeclarationNode, Name))
		{
			int32 Index = ScopedVariables.Add(FXMSScopedVariable(Name, Type, DeclarationNode));
			
			const FXMSScopedVariable& NewScopedVariable = ScopedVariables[Index];
			// Since it is a new variable, I use new name and type as old too
			DeclaredVariableListChangedDelegate.Broadcast(NewScopedVariable.Name, NewScopedVariable.Type, NewScopedVariable.Name, NewScopedVariable.Type);
		}
		return;
	}

	bool bUpdated = false;
	FString OldName = ScopedVariable->Name;
	int32 OldType = ScopedVariable->Type;

	// We can only change name if there is not another variable of this name in scope
	if (ScopedVariable->Name != Name && !HasVariableInScope(DeclarationNode, Name))
	{
		ScopedVariable->Name = Name;
		bUpdated = true;
	}

	// We can change type freely because name uniqueness is checked across types
	if (ScopedVariable->Type != Type)
	{
		ScopedVariable->Type = Type;
		bUpdated = true;
	}

	if (bUpdated)
	{
		DeclaredVariableListChangedDelegate.Broadcast(ScopedVariable->Name, ScopedVariable->Type, OldName, OldType);
	}
}

void UXMSSpellEditorComponent::UpdateVariableType(UXMSVariableDeclarationNode* DeclarationNode, int32 Type)
{
	FXMSScopedVariable* ScopedVariable = GetVariable(DeclarationNode);
	if (!ScopedVariable) return;

	if (ScopedVariable->Type != Type)
	{
		int32 OldType = ScopedVariable->Type;
		ScopedVariable->Type = Type;
		// Since name did not change, I use new name as old too
		DeclaredVariableListChangedDelegate.Broadcast(ScopedVariable->Name, ScopedVariable->Type, ScopedVariable->Name, OldType);
	}
}

void UXMSSpellEditorComponent::UnRegisterVariable(UXMSVariableDeclarationNode* DeclarationNode)
{
	for (auto It = ScopedVariables.CreateIterator(); It; ++It)
	{
		FXMSScopedVariable& ScopedVariable = *It;
		if (DeclarationNode == ScopedVariable.DeclarationNode.Get())
		{
			FString VariableName = ScopedVariable.Name;
			int32 VariableType = ScopedVariable.Type;
			
			It.RemoveCurrent();
			// Since we are removing the variable, I use new name and type as old too
			DeclaredVariableListChangedDelegate.Broadcast(VariableName, VariableType, VariableName, VariableType);
		}
	}
}

void UXMSSpellEditorComponent::GetVariablesNamesByType(int32 Type, const UXMSNode* RequestingNode, TArray<FString>& OutVariableNames) const
{
	if (!RequestingNode) return;
	
	TArray<UXMSNode*> RequestingNodeHierarchy;
	RequestingNode->GetHierarchy(RequestingNodeHierarchy);
	
	for (const FXMSScopedVariable& ScopedVariable : ScopedVariables)
	{
		if (ScopedVariable.Type == Type)
		{
			// We only want to add the variable if Node is in scope of the node that created the variable
			if (RequestingNode->IsInScopeOf(ScopedVariable.DeclarationNode.Get(), RequestingNodeHierarchy))
			{
				OutVariableNames.Add(ScopedVariable.Name);
			}
		}
	}
}

bool UXMSSpellEditorComponent::HasVariableInScope(UXMSNode* RequestingNode, const FString& Name, int32 Type) const
{
	if (!RequestingNode) return false;

	// Get Hierarchy of RequestingNode
	TArray<UXMSNode*> RequestingNodeHierarchy;
	RequestingNode->GetHierarchy(RequestingNodeHierarchy);
	
	if (Type != XMSVariableType::EVT_None)
	{
		// Check by type first to decrease string comparison
		return ScopedVariables.ContainsByPredicate([RequestingNode, RequestingNodeHierarchy, Name, Type](const FXMSScopedVariable& Variable)
			{
				return Type == Variable.Type && Name.Equals(Variable.Name) && RequestingNode->IsInScopeOf(Variable.DeclarationNode.Get(), RequestingNodeHierarchy);
			});
	}

	// No type check
	return ScopedVariables.ContainsByPredicate([RequestingNode, RequestingNodeHierarchy, Name](const FXMSScopedVariable& Variable)
		{
			return Name.Equals(Variable.Name) && RequestingNode->IsInScopeOf(Variable.DeclarationNode.Get(), RequestingNodeHierarchy);
		});
}

bool UXMSSpellEditorComponent::HasVariable(UXMSVariableDeclarationNode* DeclarationNode) const
{
	return ScopedVariables.ContainsByPredicate([DeclarationNode](const FXMSScopedVariable& Variable)
			{
				return DeclarationNode == Variable.DeclarationNode.Get();
			});
}

FXMSScopedVariable* UXMSSpellEditorComponent::GetVariable(UXMSVariableDeclarationNode* DeclarationNode)
{
	return ScopedVariables.FindByPredicate([DeclarationNode](const FXMSScopedVariable& Variable)
			{
				return DeclarationNode == Variable.DeclarationNode.Get();
			});
}

/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/

UXMSNodeCanvasWidget* UXMSSpellEditorComponent::CreateNodeCanvas(APlayerController* PlayerController)
{
	if (!PlayerController) return nullptr;

	UXMSModularSpellsSubsystem* MSS = UXMSModularSpellsSubsystem::Get();
	if (!MSS) return nullptr;
	UXMSNodeDataRegistry* NodeDataRegistry = MSS->GetNodeDataRegistry();
	if (!NodeDataRegistry) return nullptr;
	
	UXMSNodeCanvasWidget* Widget = CreateWidget<UXMSNodeCanvasWidget>(PlayerController, NodeDataRegistry->NodeCanvasWidgetClass);
	if (Widget)
	{
		Widget->SetSpellEditorComponent(this);
	}
	return Widget;
}

/*--------------------------------------------------------------------------------------------------------------------*/

