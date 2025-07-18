// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/ValueSelector/XMSVarNameSelectorWidget.h"

#include "Node/Variable/XMSVariableNameValueNode.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"
#include "UI/NodeOptions/XMSNodeOptionsSelectionWidget.h"
#include "UI/NodeOptions/Entry/XMSStringOptionEntryWidget.h"


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
		VariableNameNode->BroadcastVariableNameChangedDelegate();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeOptionsInterface Interface
 */

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
	
	TArray<UXMSStringOptionEntryWidget*> OptionWidgets;
	OptionsSelectionWidget->InitializeOptions<UXMSStringOptionEntryWidget>(Options.Num(), VarNameOptionWidgetClass, OptionWidgets, true);

	for (auto It = OptionWidgets.CreateIterator(); It; ++It)
	{
		if (!Options.IsValidIndex(It.GetIndex()))
		{
			UE_LOG(LogXyloModularSpells, Warning, TEXT("UXMSVarNameSelectorWidget::InitializeOptions >> No matching class option for option widget??"))
			break;
		}
		if (UXMSStringOptionEntryWidget* OptionWidget = *It)
		{
			OptionWidget->SetOptionName(Options[It.GetIndex()]);
			OptionWidget->StringOptionSelectedDelegate.AddUObject(this, &UXMSVarNameSelectorWidget::ChangeVarName);
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

void UXMSVarNameSelectorWidget::OnOwningNodeVarNameChanged(const FString& NewName, const FString& OldName, bool bValidName)
{
	OnVarNameChanged(bValidName ? NewName : OldName, bValidName);
	BP_OnVarNameChanged(bValidName ? NewName : OldName, bValidName);
}

void UXMSVarNameSelectorWidget::OnVarNameChanged(const FString& InName, bool bValidName)
{
	SelectorDisplayWidget->SetDisplayText(!InName.IsEmpty() ? InName : FString(TEXT("[None]")), bValidName ? FLinearColor::White : FLinearColor::Red);
}
