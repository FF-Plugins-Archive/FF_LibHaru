// Some copyright should be here...

using System;
using System.IO;
using UnrealBuildTool;

public class FF_LibHaru : ModuleRules
{
	public FF_LibHaru(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        if (UnrealTargetPlatform.Win64 == Target.Platform)
        {
            string Location_Libharu = "../Source/FF_LibHaru/ThirdParty/libharu/Windows/include";
            PrivateIncludePaths.Add(Location_Libharu);

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty", "libharu", "Windows", "lib", "hpdf.lib"));
        }

        if (UnrealTargetPlatform.Android == Target.Platform)
        {
            // We need it for #include "AndroidPlatform.h" in fpdview.h. Because default #define DLLEXPORT makes clash with Unreal's defination. We comment it out and include AndroidPlatform.h
            PublicIncludePaths.Add(Path.Combine(EngineDirectory, "Source", "Runtime", "Core", "Public", "Android"));

            string Location_Libharu = "../Source/FF_LibHaru/ThirdParty/libharu/Android/include";
            PrivateIncludePaths.Add(Location_Libharu);

            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty", "libharu", "Android", "lib", "arm64-v8a", "libhpdf.so"));

            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "FF_LibHaru_UPL_Android.xml"));
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
