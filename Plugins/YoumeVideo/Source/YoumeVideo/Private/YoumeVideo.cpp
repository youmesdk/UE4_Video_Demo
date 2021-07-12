// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "YoumeVideo.h"

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "RHI.h"
#include "GlobalShader.h"
#include "RHICommandList.h"
#include "RenderGraphBuilder.h"
#include "RenderTargetPool.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"

#if PLATFORM_MAC
#import <AVFoundation/AVFoundation.h>
#endif

#define LOCTEXT_NAMESPACE "FYoumeVideoModule"

void FYoumeVideoModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    
    
// #if PLATFORM_MAC
#if 0
    // Request permission to access the camera and microphone.
    switch ([AVCaptureDevice authorizationStatusForMediaType : AVMediaTypeAudio])
    {
        case AVAuthorizationStatusAuthorized:
        {
            UE_LOG(LogTemp, Log, TEXT("AVAuthorizationStatusAuthorized"));
            // The user has previously granted access
            // break;
        }
        case AVAuthorizationStatusNotDetermined:
        {
            // The app hasn't yet asked the user for mic access.
            [AVCaptureDevice requestAccessForMediaType : AVMediaTypeAudio completionHandler : ^ (BOOL granted) {
            if (granted) {
                UE_LOG(LogTemp, Log, TEXT("AVAuthorizationStatusNotDetermined 1"));
            }
            }] ;
            // return true;
            UE_LOG(LogTemp, Log, TEXT("AVAuthorizationStatusNotDetermined 2"));
        }
        case AVAuthorizationStatusDenied:
        {
            UE_LOG(LogTemp, Log, TEXT("AVAuthorizationStatusDenied"));
            // The user has previously denied access.
            // return false;
        }
        case AVAuthorizationStatusRestricted:
        {
            UE_LOG(LogTemp, Log, TEXT("AVAuthorizationStatusRestricted"));
            // The user can't grant access due to restrictions.
            // return false;
        }
    }
#endif
    
}

void FYoumeVideoModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FYoumeVideoModule, YoumeVideo)
