// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/ValueSelector/XMSValueTypeSelectorWidget.h"

#include "XMSNodeStaticLibrary.h"
#include "Node/Variable/XMSValueTypeValueNode.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"
#include "UI/NodeOptions/XMSNodeOptionsSelectionWidget.h"
#include "UI/NodeOptions/Entry/XMSValueTypeOptionEntryWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSValueTypeSelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ValueTypeIcon)
	{
		ValueTypeIcon->NodeIconClickedDelegate.AddUObject(this, &UXMSValueTypeSelectorWidget::BroadcastOptionsRequestedDelegate);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeCanvasEntryWidget
 */

void UXMSValueTypeSelectorWidget::OnOwningNodeSet()
{
	Super::OnOwningNodeSet();

	NotifyTypeChange();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeOptionsInterface Interface
 */

void UXMSValueTypeSelectorWidget::BroadcastOptionsRequestedDelegate()
{
	OptionsRequestedDelegate.Broadcast(this);
}

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
			UE_LOG(LogXyloModularSpells, Warning, TEXT("UXMSNodeContainerWidget::InitializeOptions >> No matching class option for option widget??"))
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

	NotifyTypeChange();
}

void UXMSValueTypeSelectorWidget::NotifyTypeChange()
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
		ValueTypeIcon->SetDisplayIcon(Icon);
	}
}
