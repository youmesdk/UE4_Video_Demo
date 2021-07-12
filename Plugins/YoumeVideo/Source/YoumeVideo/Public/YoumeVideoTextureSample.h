// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMediaTextureSample.h"
#include "MediaObjectPool.h"
#include "Math/IntPoint.h"
#include "Math/Range.h"
#include "Misc/Timespan.h"

#if WITH_ENGINE
#include "RHI.h"
#else
#include "Containers/Array.h"
#endif

/**
 * 
 */
class YOUMEVIDEO_API FYoumeVideoTextureSample
	: public IMediaTextureSample
	, public IMediaPoolable
{
public:

	/** Virtual destructor. */
	virtual ~FYoumeVideoTextureSample() { }

public:

#if WITH_ENGINE

	/**
	 * Initialize the texture sample with a texture resource.
	 *
	 * @param InTexture The texture resource containing the video frame.
	 * @param InDim The sample buffer's width and height (in pixels).
	 * @param InOutputDim The sample's output width and height (in pixels).
	 * @param InTime The sample time (in the player's local clock).
	 * @param InDuration The duration for which the sample is valid.
	 * @return true on success, false otherwise.
	 */
	bool Initialize(
		TRefCountPtr<FRHITexture2D>& InTexture,
		const FIntPoint& InDim,
		const FIntPoint& InOutputDim)
	{
		if (!InTexture.IsValid())
		{
			return false;
		}

		Dim = InDim;
		OutputDim = InOutputDim;
		Texture = InTexture;

		return true;
	}

#else

	/**
	 * Initialize the texture sample with a memory buffer.
	 *
	 * @param InBuffer The memory buffer containing the video frame.
	 * @param InDim The sample buffer's width and height (in pixels).
	 * @param InOutputDim The sample's output width and height (in pixels).
	 * @param InStride Number of bytes per pixel row.
	 * @param InTime The sample time (in the player's local clock).
	 * @param InDuration The duration for which the sample is valid.
	 * @return true on success, false otherwise.
	 */
	bool Initialize(
		uint8* InBuffer,
		const FIntPoint& InDim,
		const FIntPoint& InOutputDim,
		uint32 InStride)
	{
		if (InBuffer == nullptr)
		{
			return false;
		}

		const int32 BufferSize = InDim.X * InDim.Y * 4;

		if (BufferSize == 0)
		{
			return false;
		}

		Buffer.Reset(BufferSize);
		Buffer.Append((uint8*)InBuffer, BufferSize);

		Dim = InDim;
		OutputDim = InOutputDim;
		Stride = InStride;

		return true;
	}
#endif

public:

	//~ IMediaTextureSample interface

	virtual const void* GetBuffer() override
	{
		return nullptr;
	}

	virtual FIntPoint GetDim() const override
	{
		return Texture->GetTexture2D()->GetSizeXY();
	}

	virtual FTimespan GetDuration() const override
	{
		return Duration;
	}

	virtual EMediaTextureSampleFormat GetFormat() const override
	{
		return EMediaTextureSampleFormat::CharBGRA;
	}

	virtual FIntPoint GetOutputDim() const override
	{
		return Texture->GetTexture2D()->GetSizeXY();
	}

	virtual uint32 GetStride() const override
	{
		return Texture->GetTexture2D()->GetSizeX() * 4;
	}

	virtual FRHITexture* GetTexture() const override
	{
		return Texture;
	}

	virtual FMediaTimeStamp GetTime() const override
	{
		return FMediaTimeStamp(Time);
	}

	virtual bool IsCacheable() const override
	{
		return true;
	}

	virtual bool IsOutputSrgb() const override
	{
		return true;
	}

	virtual void Reset() override
	{
		Texture = nullptr;
	}

private:

	/** Width and height of the texture sample. */
	FIntPoint Dim;

	/** Duration for which the sample is valid. */
	FTimespan Duration;

	/** Width and height of the output. */
	FIntPoint OutputDim;

	/** Sample time. */
	FTimespan Time;

#if WITH_ENGINE
	/** The sample's texture resource. */
	TRefCountPtr<FRHITexture2D> Texture;

#else
	/** The sample's data buffer. */
	TArray<uint8> Buffer;

	/** Number of bytes per pixel row. */
	uint32 Stride;

#endif
};

/** Implements a pool for AVF texture sample objects. */
class FYoumeVideoTextureSamplePool : public TMediaObjectPool<FYoumeVideoTextureSample> { };
