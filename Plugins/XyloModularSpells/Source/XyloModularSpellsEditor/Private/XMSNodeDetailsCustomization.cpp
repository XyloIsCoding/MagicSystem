// Fill out your copyright notice in the Description page of Project Settings.

#include "XMSNodeDetailsCustomization.h"


#include "DetailLayoutBuilder.h"


TSharedRef<IDetailCustomization> FXMSNodeDetailsCustomization::MakeInstance()
{
	return MakeShared<FXMSNodeDetailsCustomization>();
}

void FXMSNodeDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);

	for (const TWeakObjectPtr<UObject>& Object : Objects)
	{
		
	}
}