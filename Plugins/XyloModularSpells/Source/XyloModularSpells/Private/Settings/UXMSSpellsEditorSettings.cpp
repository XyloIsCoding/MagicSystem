// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/UXMSSpellsEditorSettings.h"



UUXMSSpellsEditorSettings::UUXMSSpellsEditorSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UDeveloperSettings Interface
 */

FName UUXMSSpellsEditorSettings::GetCategoryName() const
{
	return FName(TEXT("Plugins"));
}

#if WITH_EDITOR

FText UUXMSSpellsEditorSettings::GetSectionText() const
{
	return NSLOCTEXT("XyloModularSpells", "XyloModularSpellsSettingsName", "XyloModularSpells Editor Settings");
}

FText UUXMSSpellsEditorSettings::GetSectionDescription() const
{
	return NSLOCTEXT("XyloModularSpells", "XyloModularSpellsSettingsDescription", "Settings for spells editor");
}

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * UUXMSSpellsEditorSettings
 */

