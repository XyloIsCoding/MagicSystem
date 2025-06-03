// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class XyloModularSpellsEditor : ModuleRules
{
    public XyloModularSpellsEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore", 
                "XyloModularSpells"
            }
        );
    }
}