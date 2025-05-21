// Copyright Yizai MathVis

using UnrealBuildTool;
using System.Collections.Generic;

public class MathVisEditorTarget : TargetRules
{
	public MathVisEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "MathVis" } );
	}
}
