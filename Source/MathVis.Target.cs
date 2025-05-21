// Copyright Yizai MathVis

using UnrealBuildTool;
using System.Collections.Generic;

public class MathVisTarget : TargetRules
{
	public MathVisTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "MathVis" } );
	}
}
