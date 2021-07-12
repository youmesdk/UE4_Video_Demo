// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using System.IO.Compression;
using UnrealBuildTool;

public class YoumeVideo : ModuleRules
{
    public YoumeVideo(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "VideoSDK/include"),
            }
        );

        if(Target.Platform == UnrealTargetPlatform.Win32)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/youme_voice_engine.lib"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/youme_voice_engine.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/youme_voice_engine.dll"));



            RuntimeDependencies.Add("$(BinaryOutputDir)/avcodec-57.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/avcodec-57.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/avdevice-57.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/avdevice-57.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/avfilter-6.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/avfilter-6.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/avformat-57.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/avformat-57.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/avutil-55.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/avutil-55.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/D3DCompiler_43.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/D3DCompiler_43.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/d3dx10_43.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/d3dx10_43.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/libgcc_s_dw2-1.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/libgcc_s_dw2-1.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/libiconv-2.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/libiconv-2.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/libscreen.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/libscreen.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/libx264-152.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/libx264-152.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/MediaApi.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/MediaApi.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/SDL2.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/SDL2.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/swresample-2.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/swresample-2.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/swscale-4.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x86/swscale-4.dll"));


        }
        else if(Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/youme_voice_engine.lib"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/youme_voice_engine.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/youme_voice_engine.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/youme_voice_engine.pdb", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/youme_voice_engine.pdb"));



            RuntimeDependencies.Add("$(BinaryOutputDir)/avcodec-57.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/avcodec-57.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/avdevice-57.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/avdevice-57.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/avfilter-6.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/avfilter-6.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/avformat-57.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/avformat-57.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/avutil-55.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/avutil-55.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/D3DCompiler_43.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/D3DCompiler_43.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/d3dx10_43.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/d3dx10_43.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/libscreen.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/libscreen.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/libx264-152.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/libx264-152.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/MediaApi.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/MediaApi.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/SDL2.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/SDL2.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/swresample-2.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/swresample-2.dll"));
            RuntimeDependencies.Add("$(BinaryOutputDir)/swscale-4.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/swscale-4.dll"));


            // RuntimeDependencies.Add("$(BinaryOutputDir)/libgcc_s_dw2-1.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/libgcc_s_dw2-1.dll"));
            // RuntimeDependencies.Add("$(BinaryOutputDir)/libiconv-2.dll", Path.Combine(ModuleDirectory, "VideoSDK/lib/x64/libiconv-2.dll"));
        }
        else if(Target.Platform == UnrealTargetPlatform.Mac)
        {
            string MACLibraryPath = Path.Combine(ModuleDirectory, "VideoSDK/lib/macos");

            PublicAdditionalLibraries.Add(Path.Combine(MACLibraryPath, "libffmpeg3.3.a"));
            PublicAdditionalLibraries.Add(Path.Combine(MACLibraryPath, "libyoume_voice_engine.a"));
            PublicAdditionalLibraries.Add(Path.Combine(MACLibraryPath, "libYouMeCommon.a"));
            PublicDelayLoadDLLs.Add(Path.Combine(MACLibraryPath, "youme_voice_engine_mac.dylib"));
            
            
            PublicAdditionalLibraries.Add("sqlite3");
            
            PublicFrameworks.Add("SystemConfiguration");
            PublicFrameworks.Add("CoreTelephony");
            PublicFrameworks.Add("AVFoundation");
            PublicFrameworks.Add("AudioToolbox");
            PublicFrameworks.Add("VideoToolbox");
            PublicFrameworks.Add("CFNetwork");
            PublicFrameworks.Add("GLKit");
        }
        else if(Target.Platform == UnrealTargetPlatform.Android)
        {
            string AndroidLibraryPath = Path.Combine(ModuleDirectory, "VideoSDK/lib/android");

            PublicSystemLibraryPaths.Add(Path.Combine(AndroidLibraryPath, "arm64-v8a"));
            PublicSystemLibraryPaths.Add(Path.Combine(AndroidLibraryPath, "armeabi"));
            PublicSystemLibraryPaths.Add(Path.Combine(AndroidLibraryPath, "armeabi-v7a"));
            PublicSystemLibraryPaths.Add(Path.Combine(AndroidLibraryPath, "x86"));

            PublicSystemLibraries.Add("youme_voice_engine");

            PublicDependencyModuleNames.AddRange(new string[] { "Launch" });
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(AndroidLibraryPath, "YoumeVideo_UPL.xml"));
        }
        else if(Target.Platform == UnrealTargetPlatform.IOS)
        {
            string IOSLibraryPath = Path.Combine(ModuleDirectory, "VideoSDK/lib/ios");

            PublicAdditionalLibraries.Add(Path.Combine(IOSLibraryPath, "libffmpeg3.3.a"));
            PublicAdditionalLibraries.Add(Path.Combine(IOSLibraryPath, "libyoume_voice_engine.a"));
            PublicAdditionalLibraries.Add(Path.Combine(IOSLibraryPath, "libYouMeCommon.a"));
            
            PublicAdditionalLibraries.Add("sqlite3.0");
            PublicAdditionalLibraries.Add("resolv.9");
            
            PublicFrameworks.Add("SystemConfiguration");
            PublicFrameworks.Add("CoreTelephony");
            PublicFrameworks.Add("AVFoundation");
            PublicFrameworks.Add("AudioToolbox");
            PublicFrameworks.Add("VideoToolbox");
            PublicFrameworks.Add("CFNetwork");
        }


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
                "RHI",
                "Renderer",
                "RenderCore",
                "Media",
                "MediaUtils",
                "YoumeVideoUasge",
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
