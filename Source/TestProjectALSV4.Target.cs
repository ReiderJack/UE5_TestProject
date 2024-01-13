

using UnrealBuildTool;
using System.Collections.Generic;

public class TestProjectALSV4Target : TargetRules
{
	public TestProjectALSV4Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "TestProjectALSV4" } );
	}
}
