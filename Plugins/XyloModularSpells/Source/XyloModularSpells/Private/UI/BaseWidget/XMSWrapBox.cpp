// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget/XMSWrapBox.h"

int32 UXMSWrapBox::AddChildAt(int32 Index, UWidget* Content)
{
	// Is like UPanelWidget::AddChild but using Insert instead of Add
	
	if ( Content == nullptr )
	{
		return INDEX_NONE;
	}

	if ( !bCanHaveMultipleChildren && GetChildrenCount() > 0 )
	{
		return INDEX_NONE;
	}

	Content->RemoveFromParent();

	EObjectFlags NewObjectFlags = RF_Transactional;
	if (HasAnyFlags(RF_Transient))
	{
		NewObjectFlags |= RF_Transient;
	}

	UPanelSlot* PanelSlot = NewObject<UPanelSlot>(this, GetSlotClass(), NAME_None, NewObjectFlags);
	PanelSlot->Content = Content;
	PanelSlot->Parent = this;

	Content->Slot = PanelSlot;
	
	int32 ReturnIndex = Slots.Insert(PanelSlot, FMath::Clamp(Index, 0, Slots.Num()));

	OnSlotAdded(PanelSlot);

	InvalidateLayoutAndVolatility();

	return ReturnIndex;
}

void UXMSWrapBox::Rebuild()
{
	TArray<UWidget*> Widgets;
	for (auto It = Slots.CreateIterator(); It; ++It)
	{
		UPanelSlot* PanelSlot = It->Get();
		if (PanelSlot && PanelSlot->Content)
		{
			Widgets.Add(PanelSlot->Content);
		}
	}
	
	ClearChildren();
	
	for (UWidget* Widget : Widgets)
	{
		AddChild(Widget);
	}
}

