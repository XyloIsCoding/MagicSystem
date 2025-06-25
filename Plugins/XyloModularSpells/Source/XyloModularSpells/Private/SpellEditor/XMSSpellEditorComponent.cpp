// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellEditor/XMSSpellEditorComponent.h"

#include "XMSModularSpellsSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Node/XMSNodeDataOverride.h"
#include "UI/XMSNodeCanvasWidget.h"
#include "UI/XMSArraySubNodeWidget.h"
#include "UI/XMSMapSubNodeWidget.h"
#include "UI/XMSNodeWithValueWidget.h"


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
		if (!HasVariable(Name))
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
	
	if (ScopedVariable->Name != Name && !HasVariable(Name))
	{
		ScopedVariable->Name = Name;
		bUpdated = true;
	}

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

UXMSNodeCanvasWidget* UXMSSpellEditorComponent::CreateNodeCanvas(APlayerController* PlayerController)
{
	if (!PlayerController) return nullptr;

	UXMSModularSpellsSubsystem* MSS = UXMSModularSpellsSubsystem::Get();
	if (!MSS) return nullptr;
	UXMSNodeDataOverride* NodesData = MSS->GetNodeDataOverride();
	if (!NodesData) return nullptr;
	
	UXMSNodeCanvasWidget* Widget = CreateWidget<UXMSNodeCanvasWidget>(PlayerController, NodesData->NodeCanvasWidgetClass);
	if (Widget)
	{
		Widget->SetSpellEditorComponent(this);
	}
	return Widget;
}

/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/

UXMSNodeWidget* UXMSSpellEditorComponent::CreateNodeWidget(APlayerController* PlayerController, UXMSNode* OwningNode)
{
	if (!OwningNode || !PlayerController) return nullptr;

	UXMSModularSpellsSubsystem* MSS = UXMSModularSpellsSubsystem::Get();
	if (!MSS) return nullptr;
	UXMSNodeDataOverride* NodesData = MSS->GetNodeDataOverride();
	if (!NodesData) return nullptr;
	FXMSNodeData* Data = NodesData->GetNodeData(OwningNode->GetClass());
	if (!Data) return nullptr;

	// Node with map
	if (UXMSNodeWithMap* NodeWithMap = Cast<UXMSNodeWithMap>(OwningNode))
	{
		bool bHasOverride = Data->WidgetClassOverride && Data->WidgetClassOverride->IsChildOf(UXMSMapSubNodeWidget::StaticClass());
		UXMSMapSubNodeWidget* Widget = CreateWidget<UXMSMapSubNodeWidget>(PlayerController, bHasOverride ? Data->WidgetClassOverride : NodesData->NodeWithMapWidgetClass);
		if (Widget)
		{
			Widget->SetSpellEditorComponent(this);
			Widget->SetMapNode(NodeWithMap);
		}
		return Widget;
	}

	// Node with array
	if (UXMSNodeWithArray* NodeWithArray = Cast<UXMSNodeWithArray>(OwningNode))
	{
		bool bHasOverride = Data->WidgetClassOverride && Data->WidgetClassOverride->IsChildOf(UXMSArraySubNodeWidget::StaticClass());
		UXMSArraySubNodeWidget* Widget = CreateWidget<UXMSArraySubNodeWidget>(PlayerController, bHasOverride ? Data->WidgetClassOverride : NodesData->NodeWithArrayWidgetClass);
		if (Widget)
		{
			Widget->SetSpellEditorComponent(this);
			Widget->SetArrayNode(NodeWithArray);
		}
		return Widget;
	}

	// Node with value
	if (UXMSNodeWithValue* NodeWithValue = Cast<UXMSNodeWithValue>(OwningNode))
	{
		if (!Data->WidgetClassOverride) return nullptr;
		if (!Data->WidgetClassOverride->IsChildOf(UXMSNodeWithValueWidget::StaticClass())) return nullptr;
		
		UXMSNodeWithValueWidget* Widget = CreateWidget<UXMSNodeWithValueWidget>(PlayerController, Data->WidgetClassOverride);
		if (Widget)
		{
			Widget->SetSpellEditorComponent(this);
			Widget->SetValueNode(NodeWithValue);
		}
		return Widget;
	}
	
	return nullptr;
}

/*--------------------------------------------------------------------------------------------------------------------*/

