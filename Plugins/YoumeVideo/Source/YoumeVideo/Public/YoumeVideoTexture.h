// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/EnumAsByte.h"
#include "Engine/Texture.h"
#include "Math/Color.h"
#include "Math/IntPoint.h"
#include "MediaSampleQueue.h"
#include "Misc/Timespan.h"
#include "Templates/Atomic.h"
#include "Templates/SharedPointer.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"
#include "YoumeVideoTexture.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class YOUMEVIDEO_API UYoumeVideoTexture : public UTexture
{
	GENERATED_UCLASS_BODY()

public:

	TEnumAsByte<TextureAddress> AddressX;

	TEnumAsByte<TextureAddress> AddressY;

	bool AutoClear;

	FLinearColor ClearColor;

public:

	/**
	 * Gets the current aspect ratio of the texture.
	 *
	 * @return Texture aspect ratio.
	 * @see GetHeight, GetWidth
	 */
	UFUNCTION(BlueprintCallable, Category = "Media|MediaTexture")
		float GetAspectRatio() const;

	/**
	 * Gets the current height of the texture.
	 *
	 * @return Texture height (in pixels).
	 * @see GetAspectRatio, GetWidth
	 */
	UFUNCTION(BlueprintCallable, Category = "Media|MediaTexture")
		int32 GetHeight() const;

	/**
	 * Gets the current width of the texture.
	 *
	 * @return Texture width (in pixels).
	 * @see GetAspectRatio, GetHeight
	 */
	UFUNCTION(BlueprintCallable, Category = "Media|MediaTexture")
		int32 GetWidth() const;

	/**
	 * Caches the next available sample time from the queue when last rendering was made
	 * @see GetNextSampleTime
	 */
	void CacheNextAvailableSampleTime(FTimespan InNextSampleTime);

	/**
	 * Gets the next sample Time. Only valid if GetAvailableSampleCount is greater than 0
	 * @note This value is cached when last render command was executed to keep single consumer requirements.
	 * @return FTimespan of the next sample or FTimespan::MinValue if no sample was available in the queue.
	 * @see GetAvailableSampleCount, CacheNextAvailableSampleTime
	 */
	FTimespan GetNextSampleTime() const;

	/**
	 * Gets the number of samples that are available
	 * @return The number of samples in the queue
	 */
	int32 GetAvailableSampleCount() const;


	/**
	 * Push New Sample
	 * @return The number of samples in the queue
	 */
	void ProcessOutputSample(const TSharedRef<IMediaTextureSample, ESPMode::ThreadSafe>& NewSample);

public:

	//~ UTexture interface.

	virtual void BeginDestroy() override;
	virtual FTextureResource* CreateResource() override;
	virtual EMaterialValueType GetMaterialType() const override;
	virtual float GetSurfaceWidth() const override;
	virtual float GetSurfaceHeight() const override;
	virtual FGuid GetExternalTextureGuid() const override;
	void SetRenderedExternalTextureGuid(const FGuid& InNewGuid);

public:

	//~ UObject interface.

	virtual FString GetDesc() override;
	virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;
	virtual void PostLoad() override;
	virtual bool IsPostLoadThreadSafe() const override;

protected:

	/**
	 * Tick the texture resource.
	 *
	 * @param Timecode The current timecode.
	 */
	void TickResource(FTimespan Timecode);

private:

	friend class FYoumeVideoTextureClockSink;

	/** The texture's media clock sink. */
	TSharedPtr<class FYoumeVideoTextureClockSink, ESPMode::ThreadSafe> ClockSink;

	/** The last Guid that was rendered and registered in the render command*/
	FGuid CurrentRenderedGuid;

	/** The default external texture GUID if no media player is assigned. */
	const FGuid DefaultGuid;

	/** Current width and height of the resource (in pixels). */
	FIntPoint Dimensions;

	/** The previously clear color. */
	FLinearColor LastClearColor;

	/** The previously used sRGB flag. */
	bool LastSrgb;

	/** Texture sample queue. */
	TSharedPtr<FMediaTextureSampleQueue, ESPMode::ThreadSafe> SampleQueue;

	/** Current size of the resource (in bytes).*/
	SIZE_T Size;

	/** Critical section to protect last rendered guid since it can be read from anywhere. */
	mutable FCriticalSection CriticalSection;

	/** Next available sample time when last render call was made */
	TAtomic<FTimespan> CachedNextSampleTime;

};
