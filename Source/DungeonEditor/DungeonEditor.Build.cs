// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class DungeonEditor : ModuleRules
{
	public DungeonEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.Add("D:\\DungeonEditor\\Source\\DungeonEditor\\Discord");

		PublicAdditionalLibraries.Add("D:\\DungeonEditor\\Binaries\\Win64\\discord_game_sdk.dll.lib");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
