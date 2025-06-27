// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/XMSNodeClassOptions.h"

void UXMSNodeClassOptions::SetOptions(const TArray<UClass*>& InOptions)
{
	Options = InOptions;
	OptionsSet();
	BP_OptionsSet();
}

void UXMSNodeClassOptions::OptionsSet()
{
}
