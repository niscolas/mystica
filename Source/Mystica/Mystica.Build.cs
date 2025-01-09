using UnrealBuildTool;

public class Mystica : ModuleRules
{
	public Mystica(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"EnhancedInput",
				"GameplayTags",
				"GameplayTasks",
				"FunctionalTesting"});
	}
}
