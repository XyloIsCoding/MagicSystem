// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellEditor/XMSSpellEditorComponent.h"


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
	FXMSScopedVariable* ScopedVariable = GetVariable(DeclarationNode);
	if (!ScopedVariable)
	{
		if (!HasVariable(Name)) ScopedVariables.Add(FXMSScopedVariable(Name, Type, DeclarationNode));
		return;
	}

	if (ScopedVariable->Name != Name && !HasVariable(Name))
	{
		ScopedVariable->Name = Name;
	}

	if (ScopedVariable->Type != Type)
	{
		ScopedVariable->Type = Type;
	}
}

void UXMSSpellEditorComponent::UpdateVariableType(UXMSVariableDeclarationNode* DeclarationNode, int32 Type)
{
	FXMSScopedVariable* ScopedVariable = GetVariable(DeclarationNode);
	if (!ScopedVariable) return;

	if (ScopedVariable->Type != Type)
	{
		ScopedVariable->Type = Type;
	}
}

void UXMSSpellEditorComponent::UnRegisterVariable(UXMSVariableDeclarationNode* DeclarationNode)
{
	for (auto It = ScopedVariables.CreateIterator(); It; ++It)
	{
		FXMSScopedVariable& ScopedVariable = *It;
		if (DeclarationNode == ScopedVariable.DeclarationNode.Get())
		{
			It.RemoveCurrent();
		}
	}
}

void UXMSSpellEditorComponent::GetVariablesNamesByType(int32 Type, const UXMSNode* RequestingNode, TArray<FString>& OutVariableNames) const
{
	if (!RequestingNode) return;
	
	TArray<UXMSNode*> Parents;
	RequestingNode->GetHierarchy(Parents);
	
	for (const FXMSScopedVariable& ScopedVariable : ScopedVariables)
	{
		if (ScopedVariable.Type == Type)
		{
			// We only want to add the variable if Node is in scope of the node that created the variable
			if (RequestingNode->IsInScopeOf(ScopedVariable.DeclarationNode.Get(), Parents))
			{
				OutVariableNames.Add(ScopedVariable.Name);
			}
		}
	}
}

bool UXMSSpellEditorComponent::HasVariable(const FString& Name, int32 Type) const
{
	if (Type != XMSVariableType::EVT_None)
	{
		// Check by type first to decrease string comparison
		return ScopedVariables.ContainsByPredicate([Name, Type](const FXMSScopedVariable& Variable)
			{
				return Type == Variable.Type && Name.Equals(Variable.Name);
			});
	}

	// No type check
	return ScopedVariables.ContainsByPredicate([Name, Type](const FXMSScopedVariable& Variable)
		{
			return Name.Equals(Variable.Name);
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
