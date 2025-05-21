// Copyright Yizai MathVis

using UnrealBuildTool;

public class MathVis : ModuleRules
{
	public MathVis(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			// Default Modules
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",

			// New Modules
			"EnhancedInput",
			"GameplayAbilities",
			"MeshDescription",
			"StaticMeshDescription",
			"Json",
			"JsonUtilities",
			"LevelSequence",
			"MovieScene",
			"MovieSceneTracks",

			// New Modules - Editor Only
			"UnrealEd",
			"AssetTools",
			"SequencerScriptingEditor",
			"MovieSceneTools",
			"MovieSceneCapture",
			"AVIWriter"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "GameplayTasks", "MeshConversion" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}