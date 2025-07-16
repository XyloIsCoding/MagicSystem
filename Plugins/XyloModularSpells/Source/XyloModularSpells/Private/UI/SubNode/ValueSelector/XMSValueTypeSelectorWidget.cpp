// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/ValueSelector/XMSValueTypeSelectorWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Components/RichTextBlock.h"
#include "Node/XMSNodeData.h"
#include "Node/XMSNodeDataRegistry.h"
#include "Node/Variable/XMSValueTypeValueNode.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"
#include "UI/NodeOptions/XMSNodeOptionsSelectionWidget.h"
#include "UI/NodeOptions/Entry/XMSValueTypeOptionEntryWidget.h"
#include "UI/NodeTooltip/XMSNodeDoubleTooltipWidget.h"
#include "UI/NodeTooltip/XMSNodeTooltipWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeCanvasEntryWidget
 */

void UXMSValueTypeSelectorWidget::OnOwningNodeSet()
{
	Super::OnOwningNodeSet();

	if (UXMSValueTypeValueNode* ValueTypeNode = Cast<UXMSValueTypeValueNode>(OwningNode.Get()))
	{
		ValueTypeNode->ValueTypeChangedDelegate.AddUObject(this, &UXMSValueTypeSelectorWidget::OnOwningNodeValueTypeChanged);
		OnOwningNodeValueTypeChanged(ValueTypeNode->GetValueType(), XMSValueType::None);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeTooltipInterface Interface
 */

void UXMSValueTypeSelectorWidget::InitializeTooltip(UXMSNodeTooltipWidget* TooltipWidget)
{
	Super::InitializeTooltip(TooltipWidget);

	if (!TooltipWidget) return;


	// NodeWithValue owning this ValueSelectorWidget
	UXMSNode* OwningNodePtr = OwningNode.Get();
	if (!OwningNodePtr) return;
	// Node owning the NodeWithValue
	UXMSNode* OwningNodeParentPtr = OwningNodePtr->GetParentNode();
	if (!OwningNodeParentPtr) return;

	// If the NodeWithValue owning this SelectorWidget is visible, then the tooltip of this selector should
	// just show the value's description
	if (!UXMSNodeStaticLibrary::IsSubNodeHiddenInEditor(OwningNodeParentPtr->GetClass(), OwningNodePtr->GetPathFromParentNode()))
	{
		UXMSValueTypeValueNode* ValueTypeNode = Cast<UXMSValueTypeValueNode>(OwningNodePtr);
		if (!ValueTypeNode) return;
	
		if (FXMSValueTypeData* ValueTypeData = UXMSNodeStaticLibrary::GetValueTypeData(ValueTypeNode->GetValueType()))
		{
			TooltipWidget->Title->SetText(ValueTypeData->Name);
			TooltipWidget->Body->SetText(ValueTypeData->Description);
		}
		return;
	}

	// Otherwise we need to give some context to this selector, so as main tooltip we use the tooltip data that the
	// owning node (NodeWithValue) would have as sub-node of its parent node
	UXMSNodeData* OwningNodeParentData = UXMSNodeStaticLibrary::GetNodeClassData(OwningNodeParentPtr->GetClass());
	if (!OwningNodeParentData) return;
	
	if (FXMSSubNodeData* SubNodeData = OwningNodeParentData->GetSubNodeData(OwningNodePtr->GetPathFromParentNode().Identifier))
	{
		TooltipWidget->Title->SetText(SubNodeData->Name);
		TooltipWidget->Body->SetText(SubNodeData->Description);
	}

	// And as second tooltip we display the value
	UXMSNodeDoubleTooltipWidget* DoubleTooltipWidget = Cast<UXMSNodeDoubleTooltipWidget>(TooltipWidget);
	if (!DoubleTooltipWidget) return;
	UXMSValueTypeValueNode* ValueTypeNode = Cast<UXMSValueTypeValueNode>(OwningNodePtr);
	if (!ValueTypeNode) return;
	
	if (FXMSValueTypeData* ValueTypeData = UXMSNodeStaticLibrary::GetValueTypeData(ValueTypeNode->GetValueType()))
	{
		DoubleTooltipWidget->SubTitle->SetText(ValueTypeData->Name);
		DoubleTooltipWidget->SubBody->SetText(ValueTypeData->Description);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeOptionsInterface Interface
 */

void UXMSValueTypeSelectorWidget::InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget)
{
	TArray<FGameplayTag> Options;
	UXMSNodeStaticLibrary::GetAllValueTypes(Options);
	
	TArray<UXMSValueTypeOptionEntryWidget*> OptionWidgets;
	OptionsSelectionWidget->InitializeOptions<UXMSValueTypeOptionEntryWidget>(Options.Num(), ValueTypeOptionWidgetClass, OptionWidgets, true);

	for (auto It = OptionWidgets.CreateIterator(); It; ++It)
	{
		if (!Options.IsValidIndex(It.GetIndex()))
		{
			UE_LOG(LogXyloModularSpells, Warning, TEXT("UXMSValueTypeSelectorWidget::InitializeOptions >> No matching class option for option widget??"))
			break;
		}
		if (UXMSValueTypeOptionEntryWidget* OptionWidget = *It)
		{
			OptionWidget->SetValueType(Options[It.GetIndex()]);
			OptionWidget->ValueTypeOptionSelectedDelegate.AddUObject(this, &UXMSValueTypeSelectorWidget::ChangeValueType);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSValueTypeSelectorWidget
 */

void UXMSValueTypeSelectorWidget::ChangeValueType(const FGameplayTag& InType)
{
	UXMSValueTypeValueNode* ValueTypeNode = Cast<UXMSValueTypeValueNode>(OwningNode.Get());
	if (!ValueTypeNode) return;

	ValueTypeNode->SetValueType(InType);
}

void UXMSValueTypeSelectorWidget::OnOwningNodeValueTypeChanged(const FGameplayTag& NewType, const FGameplayTag& OldType)
{
	UXMSValueTypeValueNode* ValueTypeNode = Cast<UXMSValueTypeValueNode>(OwningNode.Get());
	if (!ValueTypeNode) return;

	FGameplayTag ValueType = ValueTypeNode->GetValueType();
	
	OnValueTypeChanged(ValueType);
	BP_OnValueTypeChanged(ValueType);
}

void UXMSValueTypeSelectorWidget::OnValueTypeChanged(const FGameplayTag& NewType)
{
	if (UTexture2D* Icon = UXMSNodeStaticLibrary::GetValueTypeIcon(NewType))
	{
		SelectorDisplayWidget->SetDisplayIcon(Icon);
	}
}
