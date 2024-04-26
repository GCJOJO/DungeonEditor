//  

using UnrealBuildTool;
using System.Collections.Generic;

public class DungeonEditorEditorTarget : TargetRules
{
	public DungeonEditorEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		bOverrideBuildEnvironment = true;
        ExtraModuleNames.AddRange( new string[] { "DungeonEditor" } );
	}
}
