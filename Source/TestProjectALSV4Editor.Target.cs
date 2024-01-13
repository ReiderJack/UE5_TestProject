

using UnrealBuildTool;
using System.Collections.Generic;

public class TestProjectALSV4EditorTarget : TargetRules
{
	public TestProjectALSV4EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "TestProjectALSV4" } );
	}
}
