// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/ValueSelector/XMSVarTypeSelectorWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/Variable/XMSVariableTypeValueNode.h"
#include "UI/NodeOptions/XMSNodeOptionsSelectionWidget.h"
#include "UI/NodeOptions/XMSVarTypeOptionEntryWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeOptionsInterface Interface
 */

void UXMSVarTypeSelectorWidget::InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget)
{
	TArray<FGameplayTag> Options;
	UXMSNodeStaticLibrary::GetAllValueTypes(Options);
	
	TArray<UXMSVarTypeOptionEntryWidget*> OptionWidgets;
	OptionsSelectionWidget->InitializeOptions<UXMSVarTypeOptionEntryWidget>(Options.Num(), ValueTypeOptionWidgetClass, OptionWidgets);

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

void UXMSVarTypeSelectorWidget::ChangeValueType(const FGameplayTag& InType)
{
	UXMSVariableTypeValueNode* VariableTypeNode = Cast<UXMSVariableTypeValueNode>(OwningNode.Get());
	if (!VariableTypeNode) return;

	VariableTypeNode->SetVariableType(InType);
}
