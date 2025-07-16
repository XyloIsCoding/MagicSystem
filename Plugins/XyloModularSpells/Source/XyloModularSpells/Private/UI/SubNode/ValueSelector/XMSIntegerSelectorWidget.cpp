// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/ValueSelector/XMSIntegerSelectorWidget.h"

#include "XyloModularSpells.h"
#include "Node/Types/Integer/XMSIntegerValueNode.h"
#include "UI/BaseWidget/XMSNodeIconWidget.h"
#include "UI/NodeOptions/XMSNodeOptionsSelectionWidget.h"
#include "UI/NodeOptions/Entry/XMSIntegerOptionEntryWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeCanvasEntryWidget
 */

void UXMSIntegerSelectorWidget::OnOwningNodeSet()
{
	Super::OnOwningNodeSet();

	if (UXMSIntegerValueNode* IntegerNode = Cast<UXMSIntegerValueNode>(OwningNode.Get()))
	{
		IntegerNode->IntegerValueChangedDelegate.AddUObject(this, &UXMSIntegerSelectorWidget::OnOwningNodeIntegerValueChanged);
		OnOwningNodeIntegerValueChanged(IntegerNode->GetIntegerUnsafe(), 0);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeOptionsInterface Interface
 */

void UXMSIntegerSelectorWidget::InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget)
{
	UXMSIntegerValueNode* IntegerNode = Cast<UXMSIntegerValueNode>(OwningNode.Get());
	if (!IntegerNode)
	{
		UE_LOG(LogXyloModularSpells, Warning, TEXT("UXMSIntegerSelectorWidget::InitializeOptions >> OwningNode is not UXMSIntegerValueNode"))
		return;
	}

	int32 Arr[] = { -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	TArray<int32> Options;
	Options.Append(Arr);
	
	TArray<UXMSIntegerOptionEntryWidget*> OptionWidgets;
	OptionsSelectionWidget->InitializeOptions<UXMSIntegerOptionEntryWidget>(Options.Num(), NumberOptionWidgetClass, OptionWidgets, false);
	
	for (auto It = OptionWidgets.CreateIterator(); It; ++It)
	{
		if (!Options.IsValidIndex(It.GetIndex()))
		{
			UE_LOG(LogXyloModularSpells, Warning, TEXT("UXMSIntegerSelectorWidget::InitializeOptions >> No matching class option for option widget??"))
			break;
		}
		if (UXMSIntegerOptionEntryWidget* OptionWidget = *It)
		{
			int32 Value = Options[It.GetIndex()];
			OptionWidget->SetOptionValue(Value, Value == -1 ? FString(TEXT("\u232B")) : FString());
			OptionWidget->IntegerOptionSelectedDelegate.AddUObject(this, &UXMSIntegerSelectorWidget::AppendDigit);
		}
	}

	OptionsSelectionWidget->SelectionCompletedDelegate.AddUObject(this, &UXMSIntegerSelectorWidget::SelectionCompleted);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSIntegerSelectorWidget
 */

void UXMSIntegerSelectorWidget::SelectionCompleted(bool bSuccess)
{
	UXMSIntegerValueNode* IntegerNode = Cast<UXMSIntegerValueNode>(OwningNode.Get());
	if (!IntegerNode) return;

	if (bSuccess)
	{
		// Push CachedNumber to node
		IntegerNode->SetInteger(CachedNumber);
	}
	else
	{
		// Reset widget CachedNumber to node's one
		OnOwningNodeIntegerValueChanged(IntegerNode->GetIntegerUnsafe(), 0);
	}
}

void UXMSIntegerSelectorWidget::AppendDigit(int32 InDigit)
{
	if (InDigit == -1)
	{
		CachedNumber = FMath::DivideAndRoundDown(CachedNumber, 10);
	}
	else
	{
		CachedNumber = CachedNumber * 10 + InDigit;
	}

	OnOwningNodeIntegerValueChanged(CachedNumber, 0);
}

void UXMSIntegerSelectorWidget::OnOwningNodeIntegerValueChanged(int32 NewNumber, int32 OldNumber)
{
	OnNumberChanged(NewNumber);
	BP_OnNumberChanged(NewNumber);
}

void UXMSIntegerSelectorWidget::OnNumberChanged(int32 InNumber)
{
	CachedNumber = InNumber;
	SelectorDisplayWidget->SetDisplayText(FString::FromInt(InNumber));
}