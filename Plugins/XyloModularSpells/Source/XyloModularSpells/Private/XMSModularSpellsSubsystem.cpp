// Fill out your copyright notice in the Description page of Project Settings.


#include "XMSModularSpellsSubsystem.h"

void UXMSModularSpellsSubsystem::RegisterNodeDataOverride(UXMSNodeDataOverride* InNodeDataOverride)
{
	if (!InNodeDataOverride) return;
	NodeDataOverride = InNodeDataOverride;
}
