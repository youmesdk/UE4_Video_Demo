// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "YoumeVideoUasge.h"

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "RHI.h"
#include "GlobalShader.h"
#include "RHICommandList.h"
#include "RenderGraphBuilder.h"
#include "RenderTargetPool.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FYoumeVideoUasgeModule"

void FYoumeVideoUasgeModule::StartupModule()
{
	FString PluginShaderDir = FPaths::ProjectPluginsDir() / FString("YoumeVideo/Shaders");
	UE_LOG(LogTemp, Log, TEXT("PluginShaderDir %s"), *PluginShaderDir);
	AddShaderSourceDirectoryMapping(TEXT("/YoumeVideoShaders"), PluginShaderDir);
}

void FYoumeVideoUasgeModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FYoumeVideoUasgeModule, YoumeVideoUasge)
