// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MagicSystem : ModuleRules
{
	public MagicSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "StructUtils", "XyloModularSpells" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
