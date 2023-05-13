// Some copyright should be here...

using System;
using System.IO;
using UnrealBuildTool;

public class UE_LibHaru : ModuleRules
{
	public UE_LibHaru(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        if (UnrealTargetPlatform.Win64 == Target.Platform)
        {
            string Location_Libharu = "../Source/UE_LibHaru/ThirdParty/libharu/Windows/include";
            PrivateIncludePaths.Add(Location_Libharu);

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty", "libharu", "Windows", "lib", "hpdf.lib"));
        }

        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "ExtendedVars"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
