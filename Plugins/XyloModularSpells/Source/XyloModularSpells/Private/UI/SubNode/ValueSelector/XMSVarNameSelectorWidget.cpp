// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/ValueSelector/XMSVarNameSelectorWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/XMSNodeDataRegistry.h"
#include "Node/Variable/XMSVariableNameValueNode.h"
#include "UI/BaseWidget/XMSNodeTextWidget.h"
#include "UI/NodeOptions/XMSNodeOptionsSelectionWidget.h"
#include "UI/NodeOptions/Entry/XMSVarNameOptionEntryWidget.h"



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSVarNameSelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (VarNameText)
	{
		VarNameText->NodeTextClickedDelegate.AddUObject(this, &UXMSVarNameSelectorWidget::BroadcastOptionsRequestedDelegate);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeCanvasEntryWidget
 */

void UXMSVarNameSelectorWidget::OnOwningNodeSet()
{
	Super::OnOwningNodeSet();

	if (UXMSVariableNameValueNode* VariableNameNode = Cast<UXMSVariableNameValueNode>(OwningNode.Get()))
	{
		VariableNameNode->VariableNameChangedDelegate.AddUObject(this, &UXMSVarNameSelectorWidget::OnOwningNodeVarNameChanged);

		FString InitialName;
		VariableNameNode->GetString(InitialName);
		OnOwningNodeVarNameChanged(InitialName, FString());
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeOptionsInterface Interface
 */

void UXMSVarNameSelectorWidget::BroadcastOptionsRequestedDelegate()
{
	OptionsRequestedDelegate.Broadcast(this);
}

void UXMSVarNameSelectorWidget::InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget)
{
	UXMSVariableNameValueNode* VariableNameNode = Cast<UXMSVariableNameValueNode>(OwningNode.Get());
	if (!VariableNameNode)
	{
		UE_LOG(LogXyloModularSpells, Warning, TEXT("UXMSVarNameSelectorWidget::InitializeOptions >> OwningNode is not UXMSVariableNameValueNode"))
		return;
	}
	
	TArray<FString> Options;
	VariableNameNode->GetOptions(Options);
	
	TArray<UXMSVarNameOptionEntryWidget*> OptionWidgets;
	OptionsSelectionWidget->InitializeOptions<UXMSVarNameOptionEntryWidget>(Options.Num(), VarNameOptionWidgetClass, OptionWidgets, true);

	for (auto It = OptionWidgets.CreateIterator(); It; ++It)
	{
		if (!Options.IsValidIndex(It.GetIndex()))
		{
			UE_LOG(LogXyloModularSpells, Warning, TEXT("UXMSNodeContainerWidget::InitializeOptions >> No matching class option for option widget??"))
			break;
		}
		if (UXMSVarNameOptionEntryWidget* OptionWidget = *It)
		{
			OptionWidget->SetVarName(Options[It.GetIndex()]);
			OptionWidget->VarNameOptionSelectedDelegate.AddUObject(this, &UXMSVarNameSelectorWidget::ChangeVarName);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSVarNameSelectorWidget
 */

void UXMSVarNameSelectorWidget::ChangeVarName(const FString& InName)
{
	UXMSVariableNameValueNode* VariableNameNode = Cast<UXMSVariableNameValueNode>(OwningNode.Get());
	if (!VariableNameNode) return;

	VariableNameNode->SetName(InName);
}

void UXMSVarNameSelectorWidget::OnOwningNodeVarNameChanged(const FString& NewName, const FString& OldName)
{
	OnVarNameChanged(NewName);
	BP_OnVarNameChanged(NewName);
}

void UXMSVarNameSelectorWidget::OnVarNameChanged(const FString& InName)
{
	VarNameText->SetDisplayText(!InName.IsEmpty() ? InName : FString(TEXT("[None]")));
}
