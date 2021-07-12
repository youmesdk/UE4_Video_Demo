// Fill out your copyright notice in the Description page of Project Settings.


#include "YoumeVideoTexture.h"
#include "ExternalTexture.h"
#include "Modules/ModuleManager.h"
#include "RenderUtils.h"
#include "RenderingThread.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "IMediaClock.h"
#include "IMediaClockSink.h"
#include "IMediaModule.h"
#include "YoumeVideoTextureResource.h"


/* Local helpers
 *****************************************************************************/

 /**
  * Media clock sink for media textures.
  */
class FYoumeVideoTextureClockSink
	: public IMediaClockSink
{
public:

	FYoumeVideoTextureClockSink(UYoumeVideoTexture& InOwner)
		: Owner(&InOwner)
	{ }

	virtual ~FYoumeVideoTextureClockSink() { }

public:

	virtual void TickRender(FTimespan DeltaTime, FTimespan Timecode) override
	{
		if (UYoumeVideoTexture* OwnerPtr = Owner.Get())
		{
			OwnerPtr->TickResource(Timecode);
		}
	}

private:

	TWeakObjectPtr<UYoumeVideoTexture> Owner;
};


/* UYoumeVideoTexture structors
 *****************************************************************************/

UYoumeVideoTexture::UYoumeVideoTexture(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, AddressX(TA_Clamp)
	, AddressY(TA_Clamp)
	, AutoClear(false)
	, ClearColor(FLinearColor::Black)
	, DefaultGuid(FGuid::NewGuid())
	, Dimensions(FIntPoint::ZeroValue)
	, Size(0)
	, CachedNextSampleTime(FTimespan::MinValue())
{
	NeverStream = true;
	SampleQueue = MakeShared<FMediaTextureSampleQueue, ESPMode::ThreadSafe>();
}


/* UYoumeVideoTexture interface
 *****************************************************************************/

float UYoumeVideoTexture::GetAspectRatio() const
{
	if (Dimensions.Y == 0)
	{
		return 0.0f;
	}

	return (float)(Dimensions.X) / Dimensions.Y;
}


int32 UYoumeVideoTexture::GetHeight() const
{
	return Dimensions.Y;
}

int32 UYoumeVideoTexture::GetWidth() const
{
	return Dimensions.X;
}

void UYoumeVideoTexture::CacheNextAvailableSampleTime(FTimespan InNextSampleTime)
{
	CachedNextSampleTime = InNextSampleTime;
}


/* UTexture interface
 *****************************************************************************/

FTextureResource* UYoumeVideoTexture::CreateResource()
{
	if (!ClockSink.IsValid())
	{
		IMediaModule* MediaModule = FModuleManager::LoadModulePtr<IMediaModule>("Media");

		if (MediaModule != nullptr)
		{
			ClockSink = MakeShared<FYoumeVideoTextureClockSink, ESPMode::ThreadSafe>(*this);
			MediaModule->GetClock().AddSink(ClockSink.ToSharedRef());
		}
	}

	return new FYoumeVideoTextureResource(*this, Dimensions, Size, ClearColor, DefaultGuid);
}


EMaterialValueType UYoumeVideoTexture::GetMaterialType() const
{
	return MCT_TextureExternal;
}


float UYoumeVideoTexture::GetSurfaceWidth() const
{
	return Dimensions.X;
}


float UYoumeVideoTexture::GetSurfaceHeight() const
{
	return Dimensions.Y;
}


FGuid UYoumeVideoTexture::GetExternalTextureGuid() const
{
	FScopeLock Lock(&CriticalSection);
	return CurrentRenderedGuid;
}

void UYoumeVideoTexture::SetRenderedExternalTextureGuid(const FGuid& InNewGuid)
{
	check(IsInRenderingThread());

	FScopeLock Lock(&CriticalSection);
	CurrentRenderedGuid = InNewGuid;
}

/* UObject interface
 *****************************************************************************/

void UYoumeVideoTexture::BeginDestroy()
{
	if (ClockSink.IsValid())
	{
		IMediaModule* MediaModule = FModuleManager::LoadModulePtr<IMediaModule>("Media");

		if (MediaModule != nullptr)
		{
			MediaModule->GetClock().RemoveSink(ClockSink.ToSharedRef());
		}

		ClockSink.Reset();
	}

	//Unregister the last rendered Guid
	const FGuid LastRendered = GetExternalTextureGuid();
	if (LastRendered.IsValid())
	{
		ENQUEUE_RENDER_COMMAND(MediaTextureUnregisterGuid)(
			[LastRendered](FRHICommandList& RHICmdList)
			{
				FExternalTextureRegistry::Get().UnregisterExternalTexture(LastRendered);
			});
	}

	Super::BeginDestroy();
}


FString UYoumeVideoTexture::GetDesc()
{
	return FString::Printf(TEXT("%ix%i [%s]"), Dimensions.X, Dimensions.Y, GPixelFormats[PF_B8G8R8A8].Name);
}


void UYoumeVideoTexture::GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize)
{
	Super::GetResourceSizeEx(CumulativeResourceSize);

	CumulativeResourceSize.AddUnknownMemoryBytes(Size);
}


void UYoumeVideoTexture::PostLoad()
{
	Super::PostLoad();
}

bool UYoumeVideoTexture::IsPostLoadThreadSafe() const
{
	return false;
}


/* UYoumeVideoTexture implementation
 *****************************************************************************/

void UYoumeVideoTexture::TickResource(FTimespan Timecode)
{
    // UE_LOG(LogTemp, Log, TEXT("111"));
    
	if (Resource == nullptr)
	{
		return;
	}
    
    // UE_LOG(LogTemp, Log, TEXT("222"));
    
    if(GetAvailableSampleCount() == 0)
    {
        return;
    }
    
    // UE_LOG(LogTemp, Log, TEXT("333 %d"), GetAvailableSampleCount());

	// set up render parameters
	FYoumeVideoTextureResource::FRenderParams RenderParams;

	RenderParams.Rate = 1.f;
	RenderParams.CanClear = AutoClear;
	RenderParams.ClearColor = ClearColor;
	RenderParams.PreviousGuid = DefaultGuid;
	RenderParams.CurrentGuid = DefaultGuid;
	RenderParams.SrgbOutput = SRGB;
    RenderParams.SampleSource = SampleQueue;

	// redraw texture resource on render thread
	FYoumeVideoTextureResource* ResourceParam = (FYoumeVideoTextureResource*)Resource;
	ENQUEUE_RENDER_COMMAND(MediaTextureResourceRender)(
		[ResourceParam, RenderParams](FRHICommandListImmediate& RHICmdList)
		{
			ResourceParam->Render(RenderParams);
		});
}

void UYoumeVideoTexture::ProcessOutputSample(const TSharedRef<IMediaTextureSample, ESPMode::ThreadSafe>& NewSample)
{
	SampleQueue->Enqueue(NewSample);
}

FTimespan UYoumeVideoTexture::GetNextSampleTime() const
{
	return CachedNextSampleTime;
}

int32 UYoumeVideoTexture::GetAvailableSampleCount() const
{
	return SampleQueue->Num();
}


