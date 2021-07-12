// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RHI.h"
#include "RenderResource.h"
#include "Shader.h"
#include "GlobalShader.h"
#include "PipelineStateCache.h"
#include "ShaderParameterStruct.h"


namespace YoumeVideoShaders
{
	/** Color transform from YUV to sRGB (using values from MSDN). */
	extern const FMatrix YuvToSrgbDefault;

	/** Color transform from YUV to sRGB (in JPEG color space). */
	extern const FMatrix YuvToSrgbJpeg;

	/** Color transform from YUV to sRGB (using values from PS4 AvPlayer codec). */
	extern const FMatrix YuvToSrgbPs4;

	/** Color transform from YUV to sRGB (in Rec. 601 color space). */
	extern const FMatrix YuvToSrgbRec601;

	/** Color transform from YUV to sRGB (in Rec. 709 color space). */
	extern const FMatrix YuvToRgbRec709;

	/** Color transform from YUV to RGB (in Rec. 709 color space, RGB full range) */
	extern const FMatrix YuvToRgbRec709Full;

	/** Color transform from RGB to YUV (in Rec. 709 color space, RGB full range) */
	extern const FMatrix RgbToYuvRec709Full;

	/** YUV Offset for 8 bit conversion (Computed as 16/255, 128/255, 128/255) */
	extern const FVector YUVOffset8bits;

	/** YUV Offset for 10 bit conversion (Computed as 64/1023, 512/1023, 512/1023) */
	extern const FVector YUVOffset10bits;

	/** Combine color transform matrix with yuv offset in a single matrix */
	FMatrix CombineColorTransformAndOffset(const FMatrix& InMatrix, const FVector& InYUVOffset);
}


/**
 * Stores media drawing vertices.
 */
struct FYoumeVideoElementVertex
{
	FVector4 Position;
	FVector2D TextureCoordinate;

	FYoumeVideoElementVertex() { }

	FYoumeVideoElementVertex(const FVector4& InPosition, const FVector2D& InTextureCoordinate)
		: Position(InPosition)
		, TextureCoordinate(InTextureCoordinate)
	{ }
};

inline FVertexBufferRHIRef CreateTempYoumeVideoVertexBuffer(float ULeft = 0.0f, float URight = 1.0f, float VTop = 0.0f, float VBottom = 1.0f)
{
	FRHIResourceCreateInfo CreateInfo;
	FVertexBufferRHIRef VertexBufferRHI = RHICreateVertexBuffer(sizeof(FYoumeVideoElementVertex) * 4, BUF_Volatile, CreateInfo);
	void* VoidPtr = RHILockVertexBuffer(VertexBufferRHI, 0, sizeof(FYoumeVideoElementVertex) * 4, RLM_WriteOnly);

	FYoumeVideoElementVertex* Vertices = (FYoumeVideoElementVertex*)VoidPtr;
	Vertices[0].Position.Set(-1.0f, 1.0f, 1.0f, 1.0f); // Top Left
	Vertices[1].Position.Set(1.0f, 1.0f, 1.0f, 1.0f); // Top Right
	Vertices[2].Position.Set(-1.0f, -1.0f, 1.0f, 1.0f); // Bottom Left
	Vertices[3].Position.Set(1.0f, -1.0f, 1.0f, 1.0f); // Bottom Right

	Vertices[0].TextureCoordinate.Set(ULeft, VTop);
	Vertices[1].TextureCoordinate.Set(URight, VTop);
	Vertices[2].TextureCoordinate.Set(ULeft, VBottom);
	Vertices[3].TextureCoordinate.Set(URight, VBottom);
	RHIUnlockVertexBuffer(VertexBufferRHI);

	return VertexBufferRHI;
}

/**
 * The simple element vertex declaration resource type.
 */
class FYoumeVideoVertexDeclaration
	: public FRenderResource
{
public:

	FVertexDeclarationRHIRef VertexDeclarationRHI;

	virtual ~FYoumeVideoVertexDeclaration() { }

	virtual void InitRHI() override
	{
		FVertexDeclarationElementList Elements;
		uint16 Stride = sizeof(FYoumeVideoElementVertex);
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FYoumeVideoElementVertex, Position), VET_Float4, 0, Stride));
		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FYoumeVideoElementVertex, TextureCoordinate), VET_Float2, 1, Stride));
		VertexDeclarationRHI = PipelineStateCache::GetOrCreateVertexDeclaration(Elements);
	}

	virtual void ReleaseRHI() override
	{
		VertexDeclarationRHI.SafeRelease();
	}
};


YOUMEVIDEOUASGE_API extern TGlobalResource<FYoumeVideoVertexDeclaration> GYoumeVideoVertexDeclaration;

/**
 * YoumeVideo vertex shader (shared by all media shaders).
 */
class FYoumeVideoShadersVS
	: public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FYoumeVideoShadersVS, Global, YOUMEVIDEOUASGE_API);

public:

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::ES3_1);
	}

	/** Default constructor. */
	FYoumeVideoShadersVS() { }

	/** Initialization constructor. */
	FYoumeVideoShadersVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{ }

	/*virtual bool Serialize(FArchive& Ar) override
	{
		bool bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);
		return bShaderHasOutdatedParameters;
	}*/
};


/**
 * Pixel shader to convert Y, U, and V planes to RGBA.
 *
 * This shader expects three textures in PF_G8 format,
 * one for each plane of Y, U, and V components.
 */
class FYoumeYUVConvertPS
	: public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FYoumeYUVConvertPS, Global, YOUMEVIDEOUASGE_API);
	SHADER_USE_PARAMETER_STRUCT(FYoumeYUVConvertPS, FGlobalShader);

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER(FMatrix, ColorTransform)
		SHADER_PARAMETER(uint32, SrgbToLinear)
		SHADER_PARAMETER(FVector2D, UVScale)
		SHADER_PARAMETER_TEXTURE(Texture2D, YTexture)
		SHADER_PARAMETER_TEXTURE(Texture2D, UTexture)
		SHADER_PARAMETER_TEXTURE(Texture2D, VTexture)
		SHADER_PARAMETER_SAMPLER(SamplerState, YSampler)
		SHADER_PARAMETER_SAMPLER(SamplerState, USampler)
		SHADER_PARAMETER_SAMPLER(SamplerState, VSampler)
		END_SHADER_PARAMETER_STRUCT()

public:

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::ES3_1);
	}

	/*virtual bool Serialize(FArchive& Ar) override
	{
		bool bShaderHasOutdatedParameters = FGlobalShader::Serialize(Ar);
		return bShaderHasOutdatedParameters;
	}*/

	YOUMEVIDEOUASGE_API void SetParameters(FRHICommandList& RHICmdList, TShaderMapRef<FYoumeYUVConvertPS> PixelShader,TRefCountPtr<FRHITexture2D> YTexture, TRefCountPtr<FRHITexture2D> UTexture, TRefCountPtr<FRHITexture2D> VTexture, const FIntPoint& OutputDimensions, const FMatrix& ColorTransform, const FVector& YUVOffset, bool SrgbToLinear);
};
