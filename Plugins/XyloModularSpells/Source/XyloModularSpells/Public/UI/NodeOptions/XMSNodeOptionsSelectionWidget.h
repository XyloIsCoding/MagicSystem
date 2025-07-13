// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XMSNodeOptionEntryWidget.h"
#include "XyloModularSpells.h"
#include "Blueprint/UserWidget.h"
#include "Components/PanelWidget.h"
#include "XMSNodeOptionsSelectionWidget.generated.h"

class UXMSNodeIconWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FXMSOptionSelectedSignature, int32)
DECLARE_MULTICAST_DELEGATE_OneParam(FXMSSelectionCompletedSignature, bool /* Success */)

/**
 * 
 */
UCLASS()
class XYLOMODULARSPELLS_API UXMSNodeOptionsSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	 * UXMSNodeOptionsSelectionWidget
	 */

public:
	template <typename EntryClass> requires std::is_base_of_v<UXMSNodeOptionEntryWidget, EntryClass>
	void InitializeOptions(int32 Size, TSubclassOf<EntryClass> OptionWidgetClass, TArray<EntryClass*>& OutEntries, bool bInSingleChoice);
protected:
	void PrepareOptionEntryWidget(UXMSNodeOptionEntryWidget* OptionEntryWidget, int32 Index);

protected:
	virtual void OnOptionsInitialized();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOptionsInitialized();
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UPanelWidget> OptionsContainer;

/*--------------------------------------------------------------------------------------------------------------------*/
	// OptionSelection

public:
	void ClearDelegates();
	
public:
	FXMSOptionSelectedSignature OptionSelectedDelegate;
protected:
	void SelectOption(int32 Index);
	virtual void OptionSelected(int32 Index);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OptionSelected(int32 Index);
	
public:
	FXMSSelectionCompletedSignature SelectionCompletedDelegate;
protected:
	UFUNCTION(BlueprintCallable)
	void BroadcastSelectionCompleted(bool bSuccess);
	virtual void SelectionCompleted(bool bSuccess);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_SelectionCompleted(bool bSuccess);
protected:
	UPROPERTY(BlueprintReadOnly)
	bool bSingleChoice = true;

	// ~OptionSelection
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
	// Tooltip

protected:
	virtual void TooltipRequested(UWidget* Widget);
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UXMSNodeTooltipWidget> OptionTooltipWidget;
	
	// ~Tooltip
/*--------------------------------------------------------------------------------------------------------------------*/
};




template <typename EntryClass> requires std::is_base_of_v<UXMSNodeOptionEntryWidget, EntryClass>
void UXMSNodeOptionsSelectionWidget::InitializeOptions(int32 Size, TSubclassOf<EntryClass> OptionWidgetClass, TArray<EntryClass*>& OutEntries, bool bInSingleChoice)
{
	if (!OptionsContainer) return;

	if (!OptionWidgetClass)
	{
		UE_LOG(LogXyloModularSpells, Warning, TEXT("UXMSNodeOptionsSelectionWidget::InitializeOptions >> No OptionWidgetClass"))
		return;
	}

	bSingleChoice = bInSingleChoice;

	int32 MaxIndex = Size - 1;
	int32 FoundIndex = -1;
	for (UWidget* Entry : OptionsContainer->GetAllChildren())
	{
		if (FoundIndex >= MaxIndex)
		{
			Entry->RemoveFromParent();
			continue;
		}
		
		if (EntryClass* CastedEntry = Cast<EntryClass>(Entry))
		{
			PrepareOptionEntryWidget(CastedEntry, ++FoundIndex);
			OutEntries.Add(CastedEntry);
		}
		else
		{
			Entry->RemoveFromParent();
		}
	}


	if (FoundIndex < MaxIndex)
	{
		int32 RemainingEntries = MaxIndex - FoundIndex;
		for (int32 i = 0; i < RemainingEntries; ++i)
		{
			if (EntryClass* NewOption = CreateWidget<EntryClass>(GetOwningPlayer(), OptionWidgetClass))
			{
				OptionsContainer->AddChild(NewOption);
				PrepareOptionEntryWidget(NewOption, ++FoundIndex);
				OutEntries.Add(NewOption);
			}
		}
	}

	OnOptionsInitialized();
	BP_OnOptionsInitialized();
}

