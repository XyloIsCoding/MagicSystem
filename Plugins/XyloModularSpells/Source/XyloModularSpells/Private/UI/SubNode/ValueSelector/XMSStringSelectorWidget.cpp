// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SubNode/ValueSelector/XMSStringSelectorWidget.h"

#include "XyloModularSpells.h"
#include "Node/Types/String/XMSStringValueNode.h"
#include "UI/BaseWidget/XMSNodeTextWidget.h"
#include "UI/NodeOptions/XMSNodeOptionsSelectionWidget.h"
#include "UI/NodeOptions/Entry/XMSStringOptionEntryWidget.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUserWidget Interface
 */

void UXMSStringSelectorWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StringText)
	{
		StringText->NodeTextClickedDelegate.AddUObject(this, &UXMSStringSelectorWidget::BroadcastOptionsRequestedDelegate);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSNodeCanvasEntryWidget
 */

void UXMSStringSelectorWidget::OnOwningNodeSet()
{
	Super::OnOwningNodeSet();

	if (UXMSStringValueNode* StringNode = Cast<UXMSStringValueNode>(OwningNode.Get()))
	{
		StringNode->StringValueChangedDelegate.AddUObject(this, &UXMSStringSelectorWidget::OnOwningNodeStringValueChanged);

		FString InitialName;
		StringNode->GetString(InitialName);
		OnOwningNodeStringValueChanged(InitialName, FString());
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * IXMSNodeOptionsInterface Interface
 */

void UXMSStringSelectorWidget::BroadcastOptionsRequestedDelegate()
{
	OptionsRequestedDelegate.Broadcast(this);
}

void UXMSStringSelectorWidget::InitializeOptions(UXMSNodeOptionsSelectionWidget* OptionsSelectionWidget)
{
	UXMSStringValueNode* StringNode = Cast<UXMSStringValueNode>(OwningNode.Get());
	if (!StringNode)
	{
		UE_LOG(LogXyloModularSpells, Warning, TEXT("UXMSStringSelectorWidget::InitializeOptions >> OwningNode is not UXMSStringValueNode"))
		return;
	}

	FString Arr[] = { TEXT("\u232B"), TEXT("a"), TEXT("b"), TEXT("c"), TEXT("d"), TEXT("e"), TEXT("f"), TEXT("g"),
		TEXT("h"), TEXT("i"), TEXT("j"), TEXT("k"), TEXT("l"), TEXT("m"), TEXT("n"), TEXT("o"), TEXT("p"), TEXT("q"),
		TEXT("r"), TEXT("s"), TEXT("t"), TEXT("u"), TEXT("v"), TEXT("w"), TEXT("x"), TEXT("y"), TEXT("z") };
	TArray<FString> Options;
	Options.Append(Arr);
	
	TArray<UXMSStringOptionEntryWidget*> OptionWidgets;
	OptionsSelectionWidget->InitializeOptions<UXMSStringOptionEntryWidget>(Options.Num(), StringOptionWidgetClass, OptionWidgets, false);

	for (auto It = OptionWidgets.CreateIterator(); It; ++It)
	{
		if (!Options.IsValidIndex(It.GetIndex()))
		{
			UE_LOG(LogXyloModularSpells, Warning, TEXT("UXMSStringSelectorWidget::InitializeOptions >> No matching class option for option widget??"))
			break;
		}
		if (UXMSStringOptionEntryWidget* OptionWidget = *It)
		{
			OptionWidget->SetOptionName(Options[It.GetIndex()]);
			OptionWidget->StringOptionSelectedDelegate.AddUObject(this, &UXMSStringSelectorWidget::AppendString);
		}
	}

	OptionsSelectionWidget->SelectionCompletedDelegate.AddUObject(this, &UXMSStringSelectorWidget::SelectionCompleted);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UXMSStringSelectorWidget
 */

void UXMSStringSelectorWidget::SelectionCompleted(bool bSuccess)
{
	UXMSStringValueNode* StringNode = Cast<UXMSStringValueNode>(OwningNode.Get());
	if (!StringNode) return;

	if (bSuccess)
	{
		// Push CachedString to node
		StringNode->SetString(CachedString);
	}
	else
	{
		// Reset widget cached string to node's one
		FString InitialName;
		StringNode->GetString(InitialName);
		OnOwningNodeStringValueChanged(InitialName, FString());
	}
}

void UXMSStringSelectorWidget::AppendString(const FString& InString)
{
	if (InString.Equals(FString(TEXT("\u232B"))))
	{
		if (!CachedString.IsEmpty())
		{
			CachedString = CachedString.Left(CachedString.Len() - 1);
		}
	}
	else
	{
		CachedString.Append(InString);
	}

	OnOwningNodeStringValueChanged(CachedString, FString());
}

void UXMSStringSelectorWidget::OnOwningNodeStringValueChanged(const FString& NewString, const FString& OldString)
{
	OnStringChanged(NewString);
	BP_OnStringChanged(NewString);
}

void UXMSStringSelectorWidget::OnStringChanged(const FString& InString)
{
	CachedString = InString;
	StringText->SetDisplayText(!InString.IsEmpty() ? InString : FString(TEXT("[None]")));
}

