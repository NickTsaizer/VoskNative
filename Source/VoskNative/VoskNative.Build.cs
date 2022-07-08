// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class VoskNative : ModuleRules
{
	public VoskNative(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
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
				"Json",
				"JsonUtilities",
				// ... add private dependencies that you statically link with here ...	
			}
			);


		string libPath = Path.Combine(PluginDirectory, "ThirdParty", "lib");
		string includePath = Path.Combine(PluginDirectory, "ThirdParty", "include");
		
		PublicIncludePaths.Add(includePath);

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			libPath = Path.Combine(libPath, "Win64");
			PublicAdditionalLibraries.Add(Path.Combine(libPath, "libvosk.lib"));
			
			RuntimeDependencies.Add("$(ProjectDir)/Binaries/Win64/libvosk.dll",Path.Combine(libPath, "libvosk.dll"));
			RuntimeDependencies.Add("$(ProjectDir)/Binaries/Win64/libwinpthread-1.dll",Path.Combine(libPath, "libwinpthread-1.dll"));
			RuntimeDependencies.Add("$(ProjectDir)/Binaries/Win64/libstdc++-6.dll",Path.Combine(libPath, "libstdc++-6.dll"));
			RuntimeDependencies.Add("$(ProjectDir)/Binaries/Win64/libgcc_s_seh-1.dll",Path.Combine(libPath, "libgcc_s_seh-1.dll"));
		}
	}
}
