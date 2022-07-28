//  

using UnrealBuildTool;
using System.Collections.Generic;

public class DungeonEditorTarget : TargetRules
{
	public DungeonEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "DungeonEditor" } );
	}
}
