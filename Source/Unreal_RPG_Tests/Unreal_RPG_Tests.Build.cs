// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Unreal_RPG_Tests : ModuleRules
{
	public Unreal_RPG_Tests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;	
		PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "InputCore", "AIModule", "UMG", "UnrealEd" });
		PublicDependencyModuleNames.AddRange(new string[] {"Unreal_RPG"});	
	}
}
