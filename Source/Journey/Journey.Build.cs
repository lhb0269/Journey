// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Journey : ModuleRules
{
	public Journey(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "NavigationSystem", "AIModule", "LevelSequence", "MovieScene" });

		PrivateDependencyModuleNames.AddRange(new string[] { "ProceduralMeshComponent", "Slate", "SlateCore", "Niagara" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
