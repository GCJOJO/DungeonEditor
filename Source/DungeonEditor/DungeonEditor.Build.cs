// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class DungeonEditor : ModuleRules
{
	public DungeonEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "BlueprintJson" , "OnlineSubsystemEOS", "EOSShared", "EOSSDK", "AdvancedSessions", "GameplayAbilities", "GameplayTags", "GameplayTasks"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// PublicIncludePaths.Add("D:\\DungeonEditor\\Source\\DungeonEditor\\Discord");

		// if(IsWin32())   PublicAdditionalLibraries.Add("D:\\DungeonEditor\\Binaries\\Win32\\discord_game_sdk.dll.lib");
		// if(IsWin64())   PublicAdditionalLibraries.Add("D:\\DungeonEditor\\Binaries\\Win64\\discord_game_sdk.dll.lib");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		PrivateDependencyModuleNames.Add("OnlineSubsystem");
	}

	private bool IsWin64()
	{
		return Target.Platform == UnrealTargetPlatform.Win64;
	}

	/*private bool IsWin32()
	{
		return Target.Platform == UnrealTargetPlatform.Win32;
	}*/
}
