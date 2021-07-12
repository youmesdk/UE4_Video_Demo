// Fill out your copyright notice in the Description page of Project Settings.


#include "YoumeVideoWork.h"
#include "Async/Async.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "ImageUtils.h"
#include "YoumeVideoAPI.h"

#include "Containers/ResourceArray.h"
#include "MediaSamples.h"
#include "Misc/ScopeLock.h"

#if WITH_ENGINE
#include "RenderingThread.h"
#include "RHI.h"
#include "MediaShaders.h"
#include "StaticBoundShaderState.h"
#include "Misc/ScopeLock.h"
#include "PipelineStateCache.h"
#include "RHIStaticStates.h"
#include "UObject/Class.h"
#endif
#include "YoumeVideoShaders.h"




void Yuv420toRGB32(uint8* rgb24, uint8* yplane, uint8* uplane, const uint8* vplane, const int32 width, const int32 height)
{
	int r, g, b;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			uint8 yp = yplane[(y * width) + x];
			uint8 up = uplane[((y / 2) * (width / 2)) + (x / 2)];
			uint8 vp = vplane[((y / 2) * (width / 2)) + (x / 2)];

			r = ((1164 * (yp - 16) + 1596 * (vp - 128)) / 1000);
			g = ((1164 * (yp - 16) - 813 * (vp - 128) - 391 * (up - 128)) / 1000);
			b = ((1164 * (yp - 16) + 2018 * (up - 128)) / 1000);

			*rgb24++ = (((r) < 0) ? 0 : (((r) > 255) ? 255 : (r)));
			*rgb24++ = (((g) < 0) ? 0 : (((g) > 255) ? 255 : (g)));
			*rgb24++ = (((b) < 0) ? 0 : (((b) > 255) ? 255 : (b)));
			// *rgba32++ = 255;
		}
	}
}

void RGB24toRGB32(uint8* rgba32, uint8* rgb24, const int32 width, const int32 height)
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			*rgba32++ = *rgb24++;
			*rgba32++ = *rgb24++;
			*rgba32++ = *rgb24++;
			*rgba32++ = 255;
		}
	}
}


class FYoumeVideoTexture2DResourceWrapper
	: public FResourceBulkDataInterface
{
public:

#if PLATFORM_MAC || PLATFORM_IOS
	FYoumeVideoTexture2DResourceWrapper(CFTypeRef InImageBuffer)
#else
	FYoumeVideoTexture2DResourceWrapper(void* InImageBuffer)
#endif
		: ImageBuffer(InImageBuffer)
	{
		check(ImageBuffer);
#if PLATFORM_MAC || PLATFORM_IOS
		CFRetain(ImageBuffer);
#endif
	}

	virtual ~FYoumeVideoTexture2DResourceWrapper()
	{
#if PLATFORM_MAC || PLATFORM_IOS
		CFRelease(ImageBuffer);
#else
		FMemory::Free(ImageBuffer);
#endif
		ImageBuffer = nullptr;
	}

public:

	//~ FResourceBulkDataInterface interface

	virtual void Discard() override
	{
		delete this;
	}

	virtual const void* GetResourceBulkData() const override
	{
		return ImageBuffer;
	}

	virtual uint32 GetResourceBulkDataSize() const override
	{
		return ImageBuffer ? ~0u : 0;
	}

	virtual EBulkDataType GetResourceType() const override
	{
		return EBulkDataType::MediaTexture;
	}

#if PLATFORM_MAC || PLATFORM_IOS
	CFTypeRef ImageBuffer;
#else
	void* ImageBuffer;
#endif
};



static 	bool IsImplementFunc(UObject* Obj, const FName& name) {
	if (!Obj) {
		return false;
	}

	UClass* pCls = Obj->GetClass();
	if (!pCls) {
		return false;
	}

	bool bImplementsInterface = pCls->ImplementsInterface(UYoumeVideoObserver::StaticClass());
	// bool bImplementedFunction = pCls->IsFunctionImplementedInScript(name);

	return bImplementsInterface;
}



FYoumeVideoWork* FYoumeVideoWork::YVWork;

IYouMeVoiceEngine* FYoumeVideoWork::YVEngine;

FYoumeVideoWork::FYoumeVideoWork()
{
	VideoSamplePool = new FYoumeVideoTextureSamplePool();
}

FYoumeVideoWork::~FYoumeVideoWork()
{
	delete VideoSamplePool;
	VideoSamplePool = nullptr;
}

FYoumeVideoWork* FYoumeVideoWork::Instance()
{
	if (NULL == YVEngine)
	{
		YVEngine = IYouMeVoiceEngine::getInstance();
	}
	if (NULL == YVWork)
	{
		YVWork = new FYoumeVideoWork();
	}
	return YVWork;
}

IYouMeVoiceEngine* FYoumeVideoWork::Manager()
{
	if (NULL == YVEngine)
	{
		YVEngine = IYouMeVoiceEngine::getInstance();
	}
	return YVEngine;
}

EYVErrorCode FYoumeVideoWork::Start(const FString pAPPKey, const FString pAPPSecret, EYVRtcServerRegion serverRegionId, const FString pExtServerRegionName)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork::Start"));

	if (NULL == YVEngine)
	{
		Manager();
	}

	YVEngine->setAVStatisticCallback(this);
	YVEngine->setAVStatisticNewCallback(this);
	YVEngine->setMicLevelCallback(10);
	YVEngine->setFarendVoiceLevelCallback(10);
	YVEngine->setMemberChangeCallback(this);
	YVEngine->setNotifyCallback(this);
	YVEngine->setRecvCustomDataCallback(this);
	YVEngine->setRestApiCallback(this);
	YVEngine->setTranslateCallback(this);
	YVEngine->setVadCallbackEnabled(true);
	YVEngine->setVideoCallback(this);
	YVEngine->setTranscriberEnabled(true, this);
	YVEngine->setVideoPreDecodeCallbackEnable(this, true);
	YVEngine->setVideoEncodeParamCallbackEnable(true);

	return YoumeVideoUtils::ConvertErrorCode(YVEngine->init(this, TCHAR_TO_UTF8(*pAPPKey), TCHAR_TO_UTF8(*pAPPSecret), YoumeVideoUtils::ReverseRtcServerRegion(serverRegionId), TCHAR_TO_UTF8(*pExtServerRegionName)));
}

EYVErrorCode FYoumeVideoWork::StartPcm(EYVPcmCallBackFlag pcmFlag, bool outputToSpeaker, int32 outputSampleRate, int32 outputChannel)
{
	return YoumeVideoUtils::ConvertErrorCode(YVEngine->setPcmCallbackEnable(this, YoumeVideoUtils::ReversePcmCallBackFlag(pcmFlag), outputToSpeaker, outputSampleRate, outputChannel));
}

void FYoumeVideoWork::Close()
{
	if (NULL == YVEngine)
	{
		return;
	}
	YVEngine->unInit();
	YVEngine->destroy();
}

void FYoumeVideoWork::BindObserver(TScriptInterface<IYoumeVideoObserver> Listener)
{
	if (nullptr == Listener.GetObject())
		return;
	YVObserver = Listener.GetObject();
}

void FYoumeVideoWork::UnbindObserver()
{
	YVObserver = NULL;
}

void FYoumeVideoWork::onEvent(const YouMeEvent event, const YouMeErrorCode error, const char* channel, const char* param)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));

	bool bIsImplemented = IsImplementFunc(YVObserver, FName(TEXT("OnEvent")));
	if (bIsImplemented == true)
	{
		UObject* tmpObt = YVObserver;
		const EYVEvent tmpEvent = YoumeVideoUtils::ConvertEvent(event);
		const EYVErrorCode tmpError = YoumeVideoUtils::ConvertErrorCode(error);
		const FString tmpChannel = FString(UTF8_TO_TCHAR(channel));
		const FString tmpParam = FString(UTF8_TO_TCHAR(param));
		AsyncTask(ENamedThreads::GameThread, [tmpObt, tmpEvent, tmpError, tmpChannel, tmpParam] {
			if (tmpObt != nullptr) {
				IYoumeVideoObserver::Execute_OnEvent(tmpObt, tmpEvent, tmpError, tmpChannel, tmpParam);
			}
			});
	}
}

void FYoumeVideoWork::onVideoFrameCallback(const char* userId, void* data, int len, int width, int height, int fmt, uint64_t timestamp)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s %d"), UTF8_TO_TCHAR(__FUNCTION__), fmt);

	if (fmt != VIDEO_FMT_YUV420P && fmt != VIDEO_FMT_RGB24)
	{
		UE_LOG(LogTemp, Log, TEXT("FMT is not YUV420P or RGB24"));
		return;
	}

	FString UserID = FString(UTF8_TO_TCHAR(userId));

	if (!UYoumeVideoAPI::UserTextures.Contains(UserID))
	{
		AsyncTask(ENamedThreads::GameThread, [UserID] {
			UYoumeVideoAPI::CreateUserTexture(UserID);
			});
		return;
	}

	double& UserTime = UYoumeVideoAPI::UserTimes.FindOrAdd(UserID);

	if (FApp::GetCurrentTime() - UserTime < FApp::GetDeltaTime() * RenderSpace)
	{
		return;
	}
	UserTime = FApp::GetCurrentTime();



	if (fmt == VIDEO_FMT_RGB24)
	{

		void* imageData = FMemory::Malloc(width * height * 4);
		RGB24toRGB32((uint8*)imageData, (uint8*)data, width, height);

		FYoumeVideoWork* Self = this;

		ENQUEUE_RENDER_COMMAND(YoumeRenderTextures)(
			[Self, UserID, imageData, width, height](FRHICommandListImmediate& RHICmdList)
			{
				FRHIResourceCreateInfo CreateInfo;
				CreateInfo.BulkData = new FYoumeVideoTexture2DResourceWrapper(imageData);
				CreateInfo.ResourceArray = nullptr;

				ETextureCreateFlags TexCreateFlags = TexCreate_Dynamic | TexCreate_NoTiling;

				TRefCountPtr<FRHITexture2D> ShaderResource = RHICreateTexture2D(width, height, PF_R8G8B8A8, 1, 1, TexCreateFlags | TexCreate_ShaderResource | TexCreate_RenderTargetable | TexCreate_SRGB, CreateInfo);

				if (ShaderResource.IsValid())
				{
					auto VideoSample = Self->VideoSamplePool->AcquireShared();
					if (VideoSample->Initialize(ShaderResource, FIntPoint(width, height), FIntPoint(width, height)))
					{
						if (UYoumeVideoAPI::UserTextures.Contains(UserID))
						{
							(*UYoumeVideoAPI::UserTextures.Find(UserID))->ProcessOutputSample(VideoSample);
						}
					}
				}

				FMemory::Free(imageData);
			});

	}
	else if (fmt == VIDEO_FMT_YUV420P)
	{

		FYoumeVideoWork* Self = this;

		void* imageData = FMemory::Malloc(width * height * 6 / 4);
		FMemory::Memcpy(imageData, data, width * height * 6 / 4);

		ENQUEUE_RENDER_COMMAND(YoumeRenderTextures)(
			[Self, UserID, imageData, width, height](FRHICommandListImmediate& RHICmdList)
			{
				FRHIResourceCreateInfo CreateInfo;

				TRefCountPtr<FRHITexture2D> DecodedY = RHICreateTexture2D(width, height, PF_G8, 1, 1, TexCreate_Dynamic, CreateInfo);
				TRefCountPtr<FRHITexture2D> DecodedU = RHICreateTexture2D(width, height / 4, PF_G8, 1, 1, TexCreate_Dynamic, CreateInfo);
				TRefCountPtr<FRHITexture2D> DecodedV = RHICreateTexture2D(width, height / 4, PF_G8, 1, 1, TexCreate_Dynamic, CreateInfo);

				ETextureCreateFlags TexCreateFlags = TexCreate_Dynamic | TexCreate_NoTiling;
				FRHIResourceCreateInfo Info;
				TRefCountPtr<FRHITexture2D> ShaderResource = RHICreateTexture2D(width, height, PF_B8G8R8A8, 1, 1, TexCreateFlags | TexCreate_ShaderResource | TexCreate_RenderTargetable | TexCreate_SRGB, Info);

				FRHICommandListImmediate& CommandList = GetImmediateCommandList_ForRenderCommand();
				{
					// copy the Y plane out of the video buffer
					{
						uint32 Stride = 0;
						void* TextureMemory = GDynamicRHI->LockTexture2D_RenderThread(CommandList, DecodedY.GetReference(), 0, RLM_WriteOnly, Stride, false);
						if (TextureMemory)
						{
							memcpy(TextureMemory, imageData, width * height);
							GDynamicRHI->UnlockTexture2D_RenderThread(CommandList, DecodedY.GetReference(), 0, false);
						}
					}

					// copy the U plane out of the video buffer
					{
						uint32 Stride = 0;
						void* TextureMemory = GDynamicRHI->LockTexture2D_RenderThread(CommandList, DecodedU.GetReference(), 0, RLM_WriteOnly, Stride, false);
						if (TextureMemory)
						{
							memcpy(TextureMemory, (void*)((uint8*)imageData + (width * height)), width * height / 4);
							GDynamicRHI->UnlockTexture2D_RenderThread(CommandList, DecodedU.GetReference(), 0, false);
						}
					}

					// copy the V plane out of the video buffer
					{
						uint32 Stride = 0;
						void* TextureMemory = GDynamicRHI->LockTexture2D_RenderThread(CommandList, DecodedV.GetReference(), 0, RLM_WriteOnly, Stride, false);
						if (TextureMemory)
						{
							memcpy(TextureMemory, (void*)((uint8*)imageData + (width * height * 5 / 4)), width * height / 4);
							GDynamicRHI->UnlockTexture2D_RenderThread(CommandList, DecodedV.GetReference(), 0, false);
						}
					}

					FRHIRenderPassInfo RPInfo(ShaderResource, ERenderTargetActions::Load_Store);
					CommandList.BeginRenderPass(RPInfo, TEXT("ConvertYUVtoRGBA"));
					{
						// configure media shaders
						auto ShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

						TShaderMapRef<FYoumeYUVConvertPS> PixelShader(ShaderMap);
						TShaderMapRef<FYoumeVideoShadersVS> VertexShader(ShaderMap);

						FGraphicsPipelineStateInitializer GraphicsPSOInit;
						{
							CommandList.ApplyCachedRenderTargets(GraphicsPSOInit);
							GraphicsPSOInit.BlendState = TStaticBlendStateWriteMask<CW_RGBA, CW_NONE, CW_NONE, CW_NONE, CW_NONE, CW_NONE, CW_NONE, CW_NONE>::GetRHI();
							GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
							GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
							GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GYoumeVideoVertexDeclaration.VertexDeclarationRHI;
							GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
							GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
							GraphicsPSOInit.PrimitiveType = PT_TriangleStrip;
						}

						SetGraphicsPipelineState(CommandList, GraphicsPSOInit);
						PixelShader->SetParameters(CommandList, PixelShader, DecodedY->GetTexture2D(), DecodedU->GetTexture2D(), DecodedV->GetTexture2D(), FIntPoint(width, height), MediaShaders::YuvToSrgbDefault, MediaShaders::YUVOffset8bits, true);

						// draw full-size quad
						FVertexBufferRHIRef VertexBuffer = CreateTempMediaVertexBuffer();
						CommandList.SetStreamSource(0, VertexBuffer, 0);
						CommandList.SetViewport(0, 0, 0.0f, width, height, 1.0f);
						CommandList.DrawPrimitive(0, 2, 1);
					}
					CommandList.EndRenderPass();
					CommandList.CopyToResolveTarget(ShaderResource, ShaderResource, FResolveParams());
				}

				if (ShaderResource.IsValid())
				{
					auto VideoSample = Self->VideoSamplePool->AcquireShared();
					if (VideoSample->Initialize(ShaderResource, FIntPoint(width, height), FIntPoint(width, height)))
					{
						if (UYoumeVideoAPI::UserTextures.Contains(UserID))
						{
							(*UYoumeVideoAPI::UserTextures.Find(UserID))->ProcessOutputSample(VideoSample);
						}
					}
				}

				FMemory::Free(imageData);

			});
	}

	UObject* tmpObt = YVObserver;

	AsyncTask(ENamedThreads::GameThread, [tmpObt, UserID] {
		if (tmpObt != nullptr) {

			IYoumeVideoObserver::Execute_OnUserTextureUpdate(tmpObt, UserID, (*UYoumeVideoAPI::UserTextures.Find(UserID)));

		}
		});

}

void FYoumeVideoWork::onVideoFrameMixedCallback(void* data, int len, int width, int height, int fmt, uint64_t timestamp)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s %d"), UTF8_TO_TCHAR(__FUNCTION__), fmt);

	if (fmt != VIDEO_FMT_YUV420P && fmt != VIDEO_FMT_RGB24)
	{
		UE_LOG(LogTemp, Log, TEXT("FMT is not YUV420P or RGB24"));
		return;
	}

	if (UYoumeVideoAPI::MixTexture == NULL)
	{
		AsyncTask(ENamedThreads::GameThread, [] {
			UYoumeVideoAPI::CreateMixTexture();
			});
		return;
	}

	if (FApp::GetCurrentTime() - UYoumeVideoAPI::MixTime < FApp::GetDeltaTime() * RenderSpace)
	{
		return;
	}
	UYoumeVideoAPI::MixTime = FApp::GetCurrentTime();

	if (fmt == VIDEO_FMT_RGB24)
	{

		void* imageData = FMemory::Malloc(width * height * 4);
		RGB24toRGB32((uint8*)imageData, (uint8*)data, width, height);

		FYoumeVideoWork* Self = this;

		ENQUEUE_RENDER_COMMAND(YoumeRenderTextures)(
			[Self, imageData, width, height](FRHICommandListImmediate& RHICmdList)
			{
				FRHIResourceCreateInfo CreateInfo;
				CreateInfo.BulkData = new FYoumeVideoTexture2DResourceWrapper(imageData);
				CreateInfo.ResourceArray = nullptr;

				ETextureCreateFlags TexCreateFlags = TexCreate_Dynamic | TexCreate_NoTiling;

				TRefCountPtr<FRHITexture2D> ShaderResource = RHICreateTexture2D(width, height, PF_R8G8B8A8, 1, 1, TexCreateFlags | TexCreate_ShaderResource | TexCreate_RenderTargetable | TexCreate_SRGB, CreateInfo);

				if (ShaderResource.IsValid())
				{
					auto VideoSample = Self->VideoSamplePool->AcquireShared();
					if (VideoSample->Initialize(ShaderResource, FIntPoint(width, height), FIntPoint(width, height)))
					{
						if (UYoumeVideoAPI::MixTexture)
						{
							UYoumeVideoAPI::MixTexture->ProcessOutputSample(VideoSample);
						}
					}
				}

				FMemory::Free(imageData);
			});

	}
	else if (fmt == VIDEO_FMT_YUV420P)
	{


		FYoumeVideoWork* Self = this;

		void* imageData = FMemory::Malloc(width * height * 6 / 4);
		FMemory::Memcpy(imageData, data, width * height * 6 / 4);

		ENQUEUE_RENDER_COMMAND(YoumeRenderTextures)(
			[Self, imageData, width, height](FRHICommandListImmediate& RHICmdList)
			{
				FRHIResourceCreateInfo CreateInfo;

				TRefCountPtr<FRHITexture2D> DecodedY = RHICreateTexture2D(width, height, PF_G8, 1, 1, TexCreate_Dynamic, CreateInfo);
				TRefCountPtr<FRHITexture2D> DecodedU = RHICreateTexture2D(width, height / 4, PF_G8, 1, 1, TexCreate_Dynamic, CreateInfo);
				TRefCountPtr<FRHITexture2D> DecodedV = RHICreateTexture2D(width, height / 4, PF_G8, 1, 1, TexCreate_Dynamic, CreateInfo);

				ETextureCreateFlags TexCreateFlags = TexCreate_Dynamic | TexCreate_NoTiling;
				FRHIResourceCreateInfo Info;
				TRefCountPtr<FRHITexture2D> ShaderResource = RHICreateTexture2D(width, height, PF_B8G8R8A8, 1, 1, TexCreateFlags | TexCreate_ShaderResource | TexCreate_RenderTargetable | TexCreate_SRGB, Info);

				FRHICommandListImmediate& CommandList = GetImmediateCommandList_ForRenderCommand();
				{
					// copy the Y plane out of the video buffer
					{
						uint32 Stride = 0;
						void* TextureMemory = GDynamicRHI->LockTexture2D_RenderThread(CommandList, DecodedY.GetReference(), 0, RLM_WriteOnly, Stride, false);
						if (TextureMemory)
						{
							memcpy(TextureMemory, imageData, width * height);
							GDynamicRHI->UnlockTexture2D_RenderThread(CommandList, DecodedY.GetReference(), 0, false);
						}
					}

					// copy the U plane out of the video buffer
					{
						uint32 Stride = 0;
						void* TextureMemory = GDynamicRHI->LockTexture2D_RenderThread(CommandList, DecodedU.GetReference(), 0, RLM_WriteOnly, Stride, false);
						if (TextureMemory)
						{
							memcpy(TextureMemory, (void*)((uint8*)imageData + (width * height)), width * height / 4);
							GDynamicRHI->UnlockTexture2D_RenderThread(CommandList, DecodedU.GetReference(), 0, false);
						}
					}

					// copy the V plane out of the video buffer
					{
						uint32 Stride = 0;
						void* TextureMemory = GDynamicRHI->LockTexture2D_RenderThread(CommandList, DecodedV.GetReference(), 0, RLM_WriteOnly, Stride, false);
						if (TextureMemory)
						{
							memcpy(TextureMemory, (void*)((uint8*)imageData + (width * height * 5 / 4)), width * height / 4);
							GDynamicRHI->UnlockTexture2D_RenderThread(CommandList, DecodedV.GetReference(), 0, false);
						}
					}

					FRHIRenderPassInfo RPInfo(ShaderResource, ERenderTargetActions::Load_Store);
					CommandList.BeginRenderPass(RPInfo, TEXT("ConvertYUVtoRGBA"));
					{
						// configure media shaders
						auto ShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

						TShaderMapRef<FYoumeYUVConvertPS> PixelShader(ShaderMap);
						TShaderMapRef<FYoumeVideoShadersVS> VertexShader(ShaderMap);

						FGraphicsPipelineStateInitializer GraphicsPSOInit;
						{
							CommandList.ApplyCachedRenderTargets(GraphicsPSOInit);
							GraphicsPSOInit.BlendState = TStaticBlendStateWriteMask<CW_RGBA, CW_NONE, CW_NONE, CW_NONE, CW_NONE, CW_NONE, CW_NONE, CW_NONE>::GetRHI();
							GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
							GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
							GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GYoumeVideoVertexDeclaration.VertexDeclarationRHI;
							GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
							GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
							GraphicsPSOInit.PrimitiveType = PT_TriangleStrip;
						}

						SetGraphicsPipelineState(CommandList, GraphicsPSOInit);
						PixelShader->SetParameters(CommandList, PixelShader, DecodedY->GetTexture2D(), DecodedU->GetTexture2D(), DecodedV->GetTexture2D(), FIntPoint(width, height), MediaShaders::YuvToSrgbDefault, MediaShaders::YUVOffset8bits, true);

						// draw full-size quad
						FVertexBufferRHIRef VertexBuffer = CreateTempMediaVertexBuffer();
						CommandList.SetStreamSource(0, VertexBuffer, 0);
						CommandList.SetViewport(0, 0, 0.0f, width, height, 1.0f);
						CommandList.DrawPrimitive(0, 2, 1);
					}
					CommandList.EndRenderPass();
					CommandList.CopyToResolveTarget(ShaderResource, ShaderResource, FResolveParams());
				}

				if (ShaderResource.IsValid())
				{
					auto VideoSample = Self->VideoSamplePool->AcquireShared();
					if (VideoSample->Initialize(ShaderResource, FIntPoint(width, height), FIntPoint(width, height)))
					{
						if (UYoumeVideoAPI::MixTexture)
						{
							UYoumeVideoAPI::MixTexture->ProcessOutputSample(VideoSample);
						}
					}
				}

				FMemory::Free(imageData);

			});
	}

	UObject* tmpObt = YVObserver;

	AsyncTask(ENamedThreads::GameThread, [tmpObt] {
		if (tmpObt != nullptr) {

			IYoumeVideoObserver::Execute_OnMixTextureUpdate(tmpObt, UYoumeVideoAPI::MixTexture);

		}
		});
}

void FYoumeVideoWork::onVideoFramePreviewCallback(void* data, int len, int width, int height, int fmt, uint64_t timestamp, int rotation, int mirror)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s %d"), UTF8_TO_TCHAR(__FUNCTION__), fmt);

	if (fmt != VIDEO_FMT_YUV420P && fmt != VIDEO_FMT_RGB24)
	{
		UE_LOG(LogTemp, Log, TEXT("FMT is not YUV420P or RGB24"));
		return;
	}

	if (UYoumeVideoAPI::MixTexture == NULL)
	{
		AsyncTask(ENamedThreads::GameThread, [] {
			UYoumeVideoAPI::CreateMixTexture();
			});
		return;
	}

	if (FApp::GetCurrentTime() - UYoumeVideoAPI::MixTime < FApp::GetDeltaTime() * RenderSpace)
	{
		return;
	}
	UYoumeVideoAPI::MixTime = FApp::GetCurrentTime();

	if (fmt == VIDEO_FMT_RGB24)
	{
		// void* rgb24Data = FMemory::Malloc(width * height * 3);
		// Yuv420toRGB32((uint8*)rgb24Data, (uint8*)data, (uint8*)data + (width * height), (uint8*)data + (width * height * 5 / 4), width, height);

		void* imageData = FMemory::Malloc(width * height * 4);
		RGB24toRGB32((uint8*)imageData, (uint8*)data, width, height);

		// FMemory::Free(rgb24Data);

		FYoumeVideoWork* Self = this;

		ENQUEUE_RENDER_COMMAND(YoumeRenderTextures)(
			[Self, imageData, width, height](FRHICommandListImmediate& RHICmdList)
			{
				FRHIResourceCreateInfo CreateInfo;
				CreateInfo.BulkData = new FYoumeVideoTexture2DResourceWrapper(imageData);
				CreateInfo.ResourceArray = nullptr;

				ETextureCreateFlags TexCreateFlags = TexCreate_Dynamic | TexCreate_NoTiling;

				TRefCountPtr<FRHITexture2D> ShaderResource = RHICreateTexture2D(width, height, PF_R8G8B8A8, 1, 1, TexCreateFlags | TexCreate_ShaderResource | TexCreate_RenderTargetable | TexCreate_SRGB, CreateInfo);

				if (ShaderResource.IsValid())
				{
					auto VideoSample = Self->VideoSamplePool->AcquireShared();
					if (VideoSample->Initialize(ShaderResource, FIntPoint(width, height), FIntPoint(width, height)))
					{
						if (UYoumeVideoAPI::MixTexture)
						{
							UYoumeVideoAPI::MixTexture->ProcessOutputSample(VideoSample);
						}
					}
				}

				FMemory::Free(imageData);
			});

	}
	else if(fmt == VIDEO_FMT_YUV420P)
	{

		FYoumeVideoWork* Self = this;

		void* imageData = FMemory::Malloc(width * height * 6 / 4);
		FMemory::Memcpy(imageData, data, width * height * 6 / 4);

		ENQUEUE_RENDER_COMMAND(YoumeRenderTextures)(
			[Self, imageData, width, height](FRHICommandListImmediate& RHICmdList)
			{
				FRHIResourceCreateInfo CreateInfo;

				TRefCountPtr<FRHITexture2D> DecodedY = RHICreateTexture2D(width, height, PF_G8, 1, 1, TexCreate_Dynamic, CreateInfo);
				TRefCountPtr<FRHITexture2D> DecodedU = RHICreateTexture2D(width, height / 4, PF_G8, 1, 1, TexCreate_Dynamic, CreateInfo);
				TRefCountPtr<FRHITexture2D> DecodedV = RHICreateTexture2D(width, height / 4, PF_G8, 1, 1, TexCreate_Dynamic, CreateInfo);

				ETextureCreateFlags TexCreateFlags = TexCreate_Dynamic | TexCreate_NoTiling;
				FRHIResourceCreateInfo Info;
				TRefCountPtr<FRHITexture2D> ShaderResource = RHICreateTexture2D(width, height, PF_B8G8R8A8, 1, 1, TexCreateFlags | TexCreate_ShaderResource | TexCreate_RenderTargetable | TexCreate_SRGB, Info);

				FRHICommandListImmediate& CommandList = GetImmediateCommandList_ForRenderCommand();
				{
					// copy the Y plane out of the video buffer
					{
						uint32 Stride = 0;
						void* TextureMemory = GDynamicRHI->LockTexture2D_RenderThread(CommandList, DecodedY.GetReference(), 0, RLM_WriteOnly, Stride, false);
						if (TextureMemory)
						{
							memcpy(TextureMemory, imageData, width * height);
							GDynamicRHI->UnlockTexture2D_RenderThread(CommandList, DecodedY.GetReference(), 0, false);
						}
					}

					// copy the U plane out of the video buffer
					{
						uint32 Stride = 0;
						void* TextureMemory = GDynamicRHI->LockTexture2D_RenderThread(CommandList, DecodedU.GetReference(), 0, RLM_WriteOnly, Stride, false);
						if (TextureMemory)
						{
							memcpy(TextureMemory, (void*)((uint8*)imageData + (width * height)), width * height / 4);
							GDynamicRHI->UnlockTexture2D_RenderThread(CommandList, DecodedU.GetReference(), 0, false);
						}
					}

					// copy the V plane out of the video buffer
					{
						uint32 Stride = 0;
						void* TextureMemory = GDynamicRHI->LockTexture2D_RenderThread(CommandList, DecodedV.GetReference(), 0, RLM_WriteOnly, Stride, false);
						if (TextureMemory)
						{
							memcpy(TextureMemory, (void*)((uint8*)imageData + (width * height * 5 / 4)), width * height / 4);
							GDynamicRHI->UnlockTexture2D_RenderThread(CommandList, DecodedV.GetReference(), 0, false);
						}
					}

					FRHIRenderPassInfo RPInfo(ShaderResource, ERenderTargetActions::Load_Store);
					CommandList.BeginRenderPass(RPInfo, TEXT("ConvertYUVtoRGBA"));
					{
						// configure media shaders
						auto ShaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);

						TShaderMapRef<FYoumeYUVConvertPS> PixelShader(ShaderMap);
						TShaderMapRef<FYoumeVideoShadersVS> VertexShader(ShaderMap);

						FGraphicsPipelineStateInitializer GraphicsPSOInit;
						{
							CommandList.ApplyCachedRenderTargets(GraphicsPSOInit);
							GraphicsPSOInit.BlendState = TStaticBlendStateWriteMask<CW_RGBA, CW_NONE, CW_NONE, CW_NONE, CW_NONE, CW_NONE, CW_NONE, CW_NONE>::GetRHI();
							GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
							GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
							GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GYoumeVideoVertexDeclaration.VertexDeclarationRHI;
							GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
							GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
							GraphicsPSOInit.PrimitiveType = PT_TriangleStrip;
						}

						SetGraphicsPipelineState(CommandList, GraphicsPSOInit);
						PixelShader->SetParameters(CommandList, PixelShader, DecodedY->GetTexture2D(), DecodedU->GetTexture2D(), DecodedV->GetTexture2D(), FIntPoint(width, height), MediaShaders::YuvToSrgbDefault, MediaShaders::YUVOffset8bits, true);

						// draw full-size quad
						FVertexBufferRHIRef VertexBuffer = CreateTempMediaVertexBuffer();
						CommandList.SetStreamSource(0, VertexBuffer, 0);
						CommandList.SetViewport(0, 0, 0.0f, width, height, 1.0f);
						CommandList.DrawPrimitive(0, 2, 1);
					}
					CommandList.EndRenderPass();
					CommandList.CopyToResolveTarget(ShaderResource, ShaderResource, FResolveParams());
				}

				if (ShaderResource.IsValid())
				{
					auto VideoSample = Self->VideoSamplePool->AcquireShared();
					if (VideoSample->Initialize(ShaderResource, FIntPoint(width, height), FIntPoint(width, height)))
					{
						if (UYoumeVideoAPI::MixTexture)
						{
							UYoumeVideoAPI::MixTexture->ProcessOutputSample(VideoSample);
						}
					}
				}

				FMemory::Free(imageData);

			});

	}

	UObject* tmpObt = YVObserver;

	AsyncTask(ENamedThreads::GameThread, [tmpObt] {
		if (tmpObt != nullptr) {

			IYoumeVideoObserver::Execute_OnMixTextureUpdate(tmpObt, UYoumeVideoAPI::MixTexture);

		}
		});

}


#if PLATFORM_MAC || PLATFORM_IOS

#import <AVFoundation/AVFoundation.h>
#import <CoreVideo/CoreVideo.h>

/** @return the rotation to use to rotate the texture to the proper direction */
int32 FYoumeVideoWork::GetRotationFromDeviceOrientation()
{
	// NOTE: The texture we are reading from is in device space and mirrored, because Apple hates us
	EDeviceScreenOrientation ScreenOrientation = FPlatformMisc::GetDeviceOrientation();
	switch (ScreenOrientation)
	{
	case EDeviceScreenOrientation::Portrait:
	{
		return kCGImagePropertyOrientationRightMirrored;
	}

	case EDeviceScreenOrientation::LandscapeLeft:
	{
		return kCGImagePropertyOrientationUpMirrored;
	}

	case EDeviceScreenOrientation::PortraitUpsideDown:
	{
		return kCGImagePropertyOrientationLeftMirrored;
	}

	case EDeviceScreenOrientation::LandscapeRight:
	{
		return kCGImagePropertyOrientationDownMirrored;
	}
	}
	// Don't know so don't rotate
	return kCGImagePropertyOrientationUp;
}

void FYoumeVideoWork::onVideoFrameCallbackGLESForIOS(const char* userId, void* buffer, int width, int height, int fmt, uint64_t timestamp)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s %d"), UTF8_TO_TCHAR(__FUNCTION__), fmt);

	if (fmt != VIDEO_FMT_CVPIXELBUFFER)
	{
		UE_LOG(LogTemp, Log, TEXT("FMT is not VIDEO_FMT_CVPIXELBUFFER"));
		return;
	}

	FString UserID = FString(UTF8_TO_TCHAR(userId));

	if (!UYoumeVideoAPI::UserTextures.Contains(UserID))
	{
		AsyncTask(ENamedThreads::GameThread, [UserID] {
			UYoumeVideoAPI::CreateUserTexture(UserID);
			});
		return;
	}

	double& UserTime = UYoumeVideoAPI::UserTimes.FindOrAdd(UserID);

	if (FApp::GetCurrentTime() - UserTime < FApp::GetDeltaTime() * RenderSpace)
	{
		return;
	}
	UserTime = FApp::GetCurrentTime();

	CVPixelBufferRef pixelBuffer = (CVPixelBufferRef)buffer;

	const int32 Width = CVPixelBufferGetWidth(pixelBuffer);
	const int32 Height = CVPixelBufferGetHeight(pixelBuffer);
	const int32 Stride = CVPixelBufferGetBytesPerRow(pixelBuffer);

	const FIntPoint Dim = FIntPoint(Stride / 4, Height);
	const FIntPoint OutputDim = FIntPoint(Width, Height);

	auto VideoSample = VideoSamplePool->AcquireShared();

	CVMetalTextureCacheRef MetalTextureCache = nullptr;
	if (!MetalTextureCache)
	{
		id<MTLDevice> Device = (id<MTLDevice>)GDynamicRHI->RHIGetNativeDevice();
		check(Device);

		CVReturn Return = CVMetalTextureCacheCreate(kCFAllocatorDefault, nullptr, Device, nullptr, &MetalTextureCache);
		check(Return == kCVReturnSuccess);
	}
	check(MetalTextureCache);


	CVMetalTextureRef TextureRef = nullptr;
	CVReturn Result = CVMetalTextureCacheCreateTextureFromImage(kCFAllocatorDefault, MetalTextureCache, pixelBuffer, nullptr, MTLPixelFormatBGRA8Unorm_sRGB, Width, Height, 0, &TextureRef);
	check(Result == kCVReturnSuccess);
	check(TextureRef);

	FRHIResourceCreateInfo CreateInfo;
	CreateInfo.BulkData = new FYoumeVideoTexture2DResourceWrapper(TextureRef);
	CreateInfo.ResourceArray = nullptr;

	uint32 TexCreateFlags = TexCreate_SRGB;
	TexCreateFlags |= TexCreate_Dynamic | TexCreate_NoTiling;

	TRefCountPtr<FRHITexture2D> ShaderResource = RHICreateTexture2D(Width, Height, PF_B8G8R8A8, 1, 1, TexCreateFlags | TexCreate_ShaderResource, CreateInfo);

	if (ShaderResource.IsValid())
	{
		if (VideoSample->Initialize(ShaderResource, Dim, OutputDim))
		{
			if (UYoumeVideoAPI::UserTextures.Contains(UserID))
			{
				(*UYoumeVideoAPI::UserTextures.Find(UserID))->ProcessOutputSample(VideoSample);
			}
		}
	}

	// UE_LOG(LogTemp, Log, TEXT("CVPixeltoRGB32 (%d, %d) %d (%d, %d) %p"), Width, Height, Stride, Stride / 4, Height, TextureRef);

	CFRelease(TextureRef);

	if (MetalTextureCache)
	{
		CFRelease(MetalTextureCache);
		MetalTextureCache = nullptr;
	}

	UObject* tmpObt = YVObserver;

	AsyncTask(ENamedThreads::GameThread, [tmpObt, UserID] {
		if (tmpObt != nullptr) {

			IYoumeVideoObserver::Execute_OnUserTextureUpdate(tmpObt, UserID, (*UYoumeVideoAPI::UserTextures.Find(UserID)));

		}
		});

}

void FYoumeVideoWork::onVideoFrameMixedCallbackGLESForIOS(void* buffer, int width, int height, int fmt, uint64_t timestamp)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s %d"), UTF8_TO_TCHAR(__FUNCTION__), fmt);

	if (fmt != VIDEO_FMT_CVPIXELBUFFER)
	{
		UE_LOG(LogTemp, Log, TEXT("FMT is not VIDEO_FMT_CVPIXELBUFFER"));
		return;
	}

	if (UYoumeVideoAPI::MixTexture == NULL)
	{
		AsyncTask(ENamedThreads::GameThread, [] {
			UYoumeVideoAPI::CreateMixTexture();
			});
		return;
	}

	if (FApp::GetCurrentTime() - UYoumeVideoAPI::MixTime < FApp::GetDeltaTime() * RenderSpace)
	{
		return;
	}
	UYoumeVideoAPI::MixTime = FApp::GetCurrentTime();

	CVPixelBufferRef pixelBuffer = (CVPixelBufferRef)buffer;

	const int32 Width = CVPixelBufferGetWidth(pixelBuffer);
	const int32 Height = CVPixelBufferGetHeight(pixelBuffer);
	const int32 Stride = CVPixelBufferGetBytesPerRow(pixelBuffer);

	const FIntPoint Dim = FIntPoint(Stride / 4, Height);
	const FIntPoint OutputDim = FIntPoint(Width, Height);

	auto VideoSample = VideoSamplePool->AcquireShared();

	CVMetalTextureCacheRef MetalTextureCache = nullptr;
	if (!MetalTextureCache)
	{
		id<MTLDevice> Device = (id<MTLDevice>)GDynamicRHI->RHIGetNativeDevice();
		check(Device);

		CVReturn Return = CVMetalTextureCacheCreate(kCFAllocatorDefault, nullptr, Device, nullptr, &MetalTextureCache);
		check(Return == kCVReturnSuccess);
	}
	check(MetalTextureCache);


	CVMetalTextureRef TextureRef = nullptr;
	CVReturn Result = CVMetalTextureCacheCreateTextureFromImage(kCFAllocatorDefault, MetalTextureCache, pixelBuffer, nullptr, MTLPixelFormatBGRA8Unorm_sRGB, Width, Height, 0, &TextureRef);
	check(Result == kCVReturnSuccess);
	check(TextureRef);

	FRHIResourceCreateInfo CreateInfo;
	CreateInfo.BulkData = new FYoumeVideoTexture2DResourceWrapper(TextureRef);
	CreateInfo.ResourceArray = nullptr;

	uint32 TexCreateFlags = TexCreate_SRGB;
	TexCreateFlags |= TexCreate_Dynamic | TexCreate_NoTiling;

	TRefCountPtr<FRHITexture2D> ShaderResource = RHICreateTexture2D(Width, Height, PF_B8G8R8A8, 1, 1, TexCreateFlags | TexCreate_ShaderResource, CreateInfo);

	if (ShaderResource.IsValid())
	{
		if (VideoSample->Initialize(ShaderResource, Dim, OutputDim))
		{
			if (UYoumeVideoAPI::MixTexture)
			{
				UYoumeVideoAPI::MixTexture->ProcessOutputSample(VideoSample);
			}
		}
	}

	// UE_LOG(LogTemp, Log, TEXT("CVPixeltoRGB32 (%d, %d) %d (%d, %d) %p"), Width, Height, Stride, Stride / 4, Height, TextureRef);

	CFRelease(TextureRef);

	if (MetalTextureCache)
	{
		CFRelease(MetalTextureCache);
		MetalTextureCache = nullptr;
	}

	UObject* tmpObt = YVObserver;

	AsyncTask(ENamedThreads::GameThread, [tmpObt] {
		if (tmpObt != nullptr) {

			IYoumeVideoObserver::Execute_OnMixTextureUpdate(tmpObt, UYoumeVideoAPI::MixTexture);

		}
		});
}

#else

void FYoumeVideoWork::onVideoFrameCallbackGLESForIOS(const char* userId, void* pixelBuffer, int width, int height, int fmt, uint64_t timestamp)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s %d"), UTF8_TO_TCHAR(__FUNCTION__), fmt);
}

void FYoumeVideoWork::onVideoFrameMixedCallbackGLESForIOS(void* pixelBuffer, int width, int height, int fmt, uint64_t timestamp)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s %d"), UTF8_TO_TCHAR(__FUNCTION__), fmt);
}

#endif

void FYoumeVideoWork::onVideoFrameCallbackGLESForAndroid(const char* userId, int textureId, float* matrix, int width, int height, int fmt, uint64_t timestamp)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s %d"), UTF8_TO_TCHAR(__FUNCTION__), fmt);
}

void FYoumeVideoWork::onVideoFrameMixedCallbackGLESForAndroid(int textureId, float* matrix, int width, int height, int fmt, uint64_t timestamp)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s %d"), UTF8_TO_TCHAR(__FUNCTION__), fmt);

#if 0
	if (fmt != VIDEO_FMT_TEXTURE)
	{
		UE_LOG(LogTemp, Log, TEXT("FMT is not VIDEO_FMT_TEXTURE"));
		return;
	}

	if (UYoumeVideoAPI::MixTexture == NULL)
	{
		AsyncTask(ENamedThreads::GameThread, [] {
			UYoumeVideoAPI::CreateMixTexture();
			});
		return;
	}

	if (FApp::GetCurrentTime() - UYoumeVideoAPI::MixTime < FApp::GetDeltaTime() * RenderSpace)
	{
		return;
	}
	UYoumeVideoAPI::MixTime = FApp::GetCurrentTime();

	const FIntPoint Dim = FIntPoint(width, height);
	const FIntPoint OutputDim = FIntPoint(width, height);

	auto VideoSample = VideoSamplePool->AcquireShared();

	void* imageData = FMemory::Malloc(width * height * 3);
	FMemory::Memcpy(imageData, matrix, width * height * 3);

	FRHIResourceCreateInfo CreateInfo;
	CreateInfo.BulkData = new FYoumeVideoTexture2DResourceWrapper(imageData);
	CreateInfo.ResourceArray = nullptr;

	uint32 TexCreateFlags = TexCreate_SRGB;
	TexCreateFlags |= TexCreate_Dynamic | TexCreate_NoTiling;

	TRefCountPtr<FRHITexture2D> ShaderResource = RHICreateTexture2D(width, height, PF_FloatRGB, 1, 1, TexCreateFlags | TexCreate_ShaderResource, CreateInfo);

	if (ShaderResource.IsValid())
	{
		if (VideoSample->Initialize(ShaderResource, Dim, OutputDim))
		{
			if (UYoumeVideoAPI::MixTexture)
			{
				UYoumeVideoAPI::MixTexture->ProcessOutputSample(VideoSample);
			}
		}
	}

	UObject* tmpObt = YVObserver;

	AsyncTask(ENamedThreads::GameThread, [tmpObt] {
		if (tmpObt != nullptr) {

			IYoumeVideoObserver::Execute_OnMixTextureUpdate(tmpObt, UYoumeVideoAPI::MixTexture);

}
		});
#endif
}

int FYoumeVideoWork::onVideoRenderFilterCallback(int textureId, int width, int height, int rotation, int mirror)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));
	return 0;
}

void FYoumeVideoWork::onAudioFrameCallback(const char* userId, void* data, int len, uint64_t timestamp)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));
}

void FYoumeVideoWork::onAudioFrameMixedCallback(void* data, int len, uint64_t timestamp)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));
}

void FYoumeVideoWork::onAVStatistic(YouMeAVStatisticType type, const char* userID, int value)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));

	bool bIsImplemented = IsImplementFunc(YVObserver, FName(TEXT("OnAVStatistic")));
	if (bIsImplemented == true)
	{
		UObject* tmpObt = YVObserver;
		const EYVAVStatisticType tmptype = YoumeVideoUtils::ConvertAVStatisticType(type);
		const FString tmpUserID(UTF8_TO_TCHAR(userID));
		const int32 tmpValue = value;
		AsyncTask(ENamedThreads::GameThread, [tmpObt, tmptype, tmpUserID, tmpValue] {
			if (tmpObt != nullptr) {
				IYoumeVideoObserver::Execute_OnAVStatistic(tmpObt, tmptype, tmpUserID, tmpValue);
			}
			});
	}

}

void FYoumeVideoWork::onAVStatisticNew(YouMeAVStatisticType type, const char* userID, int value, const char* param)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));

	bool bIsImplemented = IsImplementFunc(YVObserver, FName(TEXT("OnAVStatisticNew")));
	if (bIsImplemented == true)
	{
		UObject* tmpObt = YVObserver;
		const EYVAVStatisticType tmptype = YoumeVideoUtils::ConvertAVStatisticType(type);
		const FString tmpUserID(UTF8_TO_TCHAR(userID));
		const int32 tmpValue = value;
		const FString tmpParam(UTF8_TO_TCHAR(param));
		AsyncTask(ENamedThreads::GameThread, [tmpObt, tmptype, tmpUserID, tmpValue, tmpParam] {
			if (tmpObt != nullptr) {
				IYoumeVideoObserver::Execute_OnAVStatisticNew(tmpObt, tmptype, tmpUserID, tmpValue, tmpParam);
			}
			});
	}
}

void FYoumeVideoWork::onPcmDataRemote(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));
}

void FYoumeVideoWork::onPcmDataRecord(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));
}

void FYoumeVideoWork::onPcmDataMix(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));
}

void FYoumeVideoWork::onSentenceBegin(std::string userid, int sentenceIndex)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));

	bool bIsImplemented = IsImplementFunc(YVObserver, FName(TEXT("OnSentenceBegin")));
	if (bIsImplemented == true)
	{
		UObject* tmpObt = YVObserver;
		const FString tmpUserid(UTF8_TO_TCHAR(userid.c_str()));
		const int32 tmpSentenceIndex = sentenceIndex;
		AsyncTask(ENamedThreads::GameThread, [tmpObt, tmpUserid, tmpSentenceIndex] {
			if (tmpObt != nullptr) {
				IYoumeVideoObserver::Execute_OnSentenceBegin(tmpObt, tmpUserid, tmpSentenceIndex);
			}
			});
	}
}

void FYoumeVideoWork::onSentenceEnd(std::string userid, int sentenceIndex, std::string result, std::string transLang /*= ""*/, std::string transResult /*= ""*/)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));

	bool bIsImplemented = IsImplementFunc(YVObserver, FName(TEXT("OnSentenceEnd")));
	if (bIsImplemented == true)
	{
		UObject* tmpObt = YVObserver;
		const FString tmpUserid(UTF8_TO_TCHAR(userid.c_str()));
		const int32 tmpSentenceIndex = sentenceIndex;
		const FString tmpResult(UTF8_TO_TCHAR(result.c_str()));
		const FString tmpTransLang(UTF8_TO_TCHAR(transLang.c_str()));
		const FString tmpTransResult(UTF8_TO_TCHAR(transResult.c_str()));
		AsyncTask(ENamedThreads::GameThread, [tmpObt, tmpUserid, tmpSentenceIndex, tmpResult, tmpTransLang, tmpTransResult] {
			if (tmpObt != nullptr) {
				IYoumeVideoObserver::Execute_OnSentenceEnd(tmpObt, tmpUserid, tmpSentenceIndex, tmpResult, tmpTransLang, tmpTransResult);
			}
			});
	}
}

void FYoumeVideoWork::onSentenceChanged(std::string userid, int sentenceIndex, std::string result, std::string transLang /*= ""*/, std::string transResult /*= ""*/)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));

	bool bIsImplemented = IsImplementFunc(YVObserver, FName(TEXT("OnSentenceChanged")));
	if (bIsImplemented == true)
	{
		UObject* tmpObt = YVObserver;
		const FString tmpUserid(UTF8_TO_TCHAR(userid.c_str()));
		const int32 tmpSentenceIndex = sentenceIndex;
		const FString tmpResult(UTF8_TO_TCHAR(result.c_str()));
		const FString tmpTransLang(UTF8_TO_TCHAR(transLang.c_str()));
		const FString tmpTransResult(UTF8_TO_TCHAR(transResult.c_str()));
		AsyncTask(ENamedThreads::GameThread, [tmpObt, tmpUserid, tmpSentenceIndex, tmpResult, tmpTransLang, tmpTransResult] {
			if (tmpObt != nullptr) {
				IYoumeVideoObserver::Execute_OnSentenceChanged(tmpObt, tmpUserid, tmpSentenceIndex, tmpResult, tmpTransLang, tmpTransResult);
			}
			});
	}
}

void FYoumeVideoWork::onTranslateTextComplete(YouMeErrorCode errorcode, unsigned int requestID, const std::string& text, YouMeLanguageCode srcLangCode, YouMeLanguageCode destLangCode)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));

	bool bIsImplemented = IsImplementFunc(YVObserver, FName(TEXT("OnVideoTranslateTextComplete")));
	if (bIsImplemented == true)
	{
		UObject* tmpObt = YVObserver;
		const EYVErrorCode tmpErrorCode = YoumeVideoUtils::ConvertErrorCode(errorcode);
		const int32 tmpRequestID = requestID;
		const FString tmpText(UTF8_TO_TCHAR(text.c_str()));
		const EYVLanguageCode tmpSrcLangCode = YoumeVideoUtils::ConvertLanguageCode(srcLangCode);
		const EYVLanguageCode tmpDestLangCode = YoumeVideoUtils::ConvertLanguageCode(destLangCode);

		AsyncTask(ENamedThreads::GameThread, [tmpObt, tmpErrorCode, tmpRequestID, tmpText, tmpSrcLangCode, tmpDestLangCode] {
			if (tmpObt != nullptr) {
				IYoumeVideoObserver::Execute_OnVideoTranslateTextComplete(tmpObt, tmpErrorCode, tmpRequestID, tmpText, tmpSrcLangCode, tmpDestLangCode);
			}
			});
	}
}

void FYoumeVideoWork::onVideoPreDecode(const char* userId, void* data, int dataSizeInByte, unsigned long long timestamp, int type)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));
}

void FYoumeVideoWork::onRequestRestAPI(int requestID, const YouMeErrorCode& iErrorCode, const char* strQuery, const char* strResult)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));


	bool bIsImplemented = IsImplementFunc(YVObserver, FName(TEXT("OnRequestRestAPI")));
	if (bIsImplemented == true)
	{
		UObject* tmpObt = YVObserver;
		const int32 tmpRequestID = requestID;
		const EYVErrorCode tmpErrorCode = YoumeVideoUtils::ConvertErrorCode(iErrorCode);
		const FString tmpStrQuery(UTF8_TO_TCHAR(strQuery));
		const FString tmpStrResult(UTF8_TO_TCHAR(strResult));

		AsyncTask(ENamedThreads::GameThread, [tmpObt, tmpRequestID, tmpErrorCode, tmpStrQuery, tmpStrResult] {
			if (tmpObt != nullptr) {
				IYoumeVideoObserver::Execute_OnRequestRestAPI(tmpObt, tmpRequestID, tmpErrorCode, tmpStrQuery, tmpStrResult);
			}
			});
	}
}

void FYoumeVideoWork::onMemberChange(const char* channel, const char* listMemberChangeJson, bool bUpdate)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));


	bool bIsImplemented = IsImplementFunc(YVObserver, FName(TEXT("OnMemberChange")));
	if (bIsImplemented == true)
	{
		UObject* tmpObt = YVObserver;
		const FString tmpChannel(UTF8_TO_TCHAR(channel));
		const FString tmpListMemberChangeJson(UTF8_TO_TCHAR(listMemberChangeJson));
		const bool tmpUpdate = bUpdate;

		AsyncTask(ENamedThreads::GameThread, [tmpObt, tmpChannel, tmpListMemberChangeJson, tmpUpdate] {
			if (tmpObt != nullptr) {
				IYoumeVideoObserver::Execute_OnMemberChange(tmpObt, tmpChannel, tmpListMemberChangeJson, tmpUpdate);
			}
			});
	}

}

void FYoumeVideoWork::onMemberChange(const char* channel, const char* userID, bool isJoin, bool bUpdate)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));


	bool bIsImplemented = IsImplementFunc(YVObserver, FName(TEXT("OnMemberJoinChange")));
	if (bIsImplemented == true)
	{
		UObject* tmpObt = YVObserver;
		const FString tmpChannel(UTF8_TO_TCHAR(channel));
		const FString tmpUserID(UTF8_TO_TCHAR(userID));
		const bool tmpJoin = bUpdate;
		const bool tmpUpdate = bUpdate;

		AsyncTask(ENamedThreads::GameThread, [tmpObt, tmpChannel, tmpUserID, tmpJoin, tmpUpdate] {
			if (tmpObt != nullptr) {
				IYoumeVideoObserver::Execute_OnMemberJoinChange(tmpObt, tmpChannel, tmpUserID, tmpJoin, tmpUpdate);
			}
			});
	}
}

void FYoumeVideoWork::onBroadcast(const YouMeBroadcast bc, const char* channel, const char* param1, const char* param2, const char* strContent)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));


	bool bIsImplemented = IsImplementFunc(YVObserver, FName(TEXT("OnBroadcast")));
	if (bIsImplemented == true)
	{
		UObject* tmpObt = YVObserver;
		const EYVBroadcast tmpBc = YoumeVideoUtils::ConvertBroadcast(bc);
		const FString tmpChannel(UTF8_TO_TCHAR(channel));
		const FString tmpParam1(UTF8_TO_TCHAR(param1));
		const FString tmpParam2(UTF8_TO_TCHAR(param2));
		const FString tmpStrContent(UTF8_TO_TCHAR(strContent));

		AsyncTask(ENamedThreads::GameThread, [tmpObt, tmpBc, tmpChannel, tmpParam1, tmpParam2, tmpStrContent] {
			if (tmpObt != nullptr) {
				IYoumeVideoObserver::Execute_OnBroadcast(tmpObt, tmpBc, tmpChannel, tmpParam1, tmpParam2, tmpStrContent);
			}
			});
	}
}

void FYoumeVideoWork::OnCustomDataNotify(const void* pData, int iDataLen, unsigned long long ulTimeSpan)
{
	UE_LOG(LogTemp, Log, TEXT("FYoumeVideoWork %s"), UTF8_TO_TCHAR(__FUNCTION__));
}
