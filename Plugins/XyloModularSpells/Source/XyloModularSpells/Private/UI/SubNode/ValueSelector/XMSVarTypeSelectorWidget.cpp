// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/ValueSelector/XMSVarTypeSelectorWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/Variable/XMSVariableTypeValueNode.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"
#include "UI/NodeOptions/XMSNodeOptionsSelectionWidget.h"
#include "UI/NodeOptions/Entry/XMSVarTypeOptionEntryWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSVarTypeSelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (VarTypeIcon)
	{
		VarTypeIcon->NodeIconClickedDelegate.AddUObject(this, &UXMSVarTypeSelectorWidget::BroadcastOptionsRequestedDelegate);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeCanvasEntryWidget
 */

void UXMSVarTypeSelectorWidget::OnOwningNodeSet()
{
	Super::OnOwningNodeSet();

	UXMSVariableTypeValueNode* VariableTypeNode = Cast<UXMSVariableTypeValueNode>(OwningNode.Get());
	if (!VariableTypeNode) return;

	FGameplayTag VarType = VariableTypeNode->GetVariableType();
	OnValueTypeChanged(VarType);
	BP_OnValueTypeChanged(VarType);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeOptionsInterface Interface
 */

void UXMSVarTypeSelectorWidget::BroadcastOptionsRequestedDelegate()
{
	OptionsRequestedDelegate.Broadcast(this);
}

void UXMSVarTypeSelectorWidget::InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget)
{
	TArray<FGameplayTag> Options;
	UXMSNodeStaticLibrary::GetAllValueTypes(Options);
	
	TArray<UXMSVarTypeOptionEntryWidget*> OptionWidgets;
	OptionsSelectionWidget->InitializeOptions<UXMSVarTypeOptionEntryWidget>(Options.Num(), ValueTypeOptionWidgetClass, OptionWidgets, true);

	for (auto It = OptionWidgets.CreateIterator(); It; ++It)
	{
		if (!Options.IsValidIndex(It.GetIndex()))
		{
			UE_LOG(LogXyloModularSpells, Warning, TEXT("UXMSNodeContainerWidget::InitializeOptions >> No matching class option for option widget??"))
			break;
		}
		if (UXMSVarTypeOptionEntryWidget* OptionWidget = *It)
		{
			OptionWidget->SetValueType(Options[It.GetIndex()]);
			OptionWidget->VarTypeOptionSelectedDelegate.AddUObject(this, &UXMSVarTypeSelectorWidget::ChangeValueType);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSVarTypeSelectorWidget
 */

void UXMSVarTypeSelectorWidget::ChangeValueType(const FGameplayTag& InType)
{
	UXMSVariableTypeValueNode* VariableTypeNode = Cast<UXMSVariableTypeValueNode>(OwningNode.Get());
	if (!VariableTypeNode) return;

	VariableTypeNode->SetVariableType(InType);

	OnValueTypeChanged(InType);
	BP_OnValueTypeChanged(InType);
}

void UXMSVarTypeSelectorWidget::OnValueTypeChanged(const FGameplayTag& NewType)
{
	if (UTexture2D* Icon = UXMSNodeStaticLibrary::GetValueTypeIcon(NewType))
	{
		VarTypeIcon->SetDisplayIcon(Icon);
	}
}
