// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BigMonD_Games : ModuleRules
{
	public BigMonD_Games(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"UMG",			// Include UMG module for User Widgets
			"Paper2D",		// Added for sprite management
			"PhysicsCore"	// Added for something I cant remember in Mario
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "Paper2D" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
