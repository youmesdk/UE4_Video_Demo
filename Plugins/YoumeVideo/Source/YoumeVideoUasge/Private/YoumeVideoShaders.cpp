// Fill out your copyright notice in the Description page of Project Settings.


#include "YoumeVideoShaders.h"
#include "ShaderParameterUtils.h"
#include "RHIStaticStates.h"
#include "GlobalShader.h"

TGlobalResource<FYoumeVideoVertexDeclaration> GYoumeVideoVertexDeclaration;

/* MediaShaders namespace
 *****************************************************************************/

namespace YoumeVideoShaders
{
	const FMatrix YuvToSrgbJpeg = FMatrix(
		FPlane(1.000000f, 0.000000f, 1.402000f, 0.000000f),
		FPlane(1.000000f, -0.344140f, -0.714140f, 0.000000f),
		FPlane(1.000000f, 1.772000f, 0.000000f, 0.000000f),
		FPlane(0.000000f, 0.000000f, 0.000000f, 0.000000f)
	);

	const FMatrix YuvToSrgbDefault = FMatrix(
		FPlane(1.164383f, 0.000000f, 1.596027f, 0.000000f),
		FPlane(1.164383f, -0.391762f, -0.812968f, 0.000000f),
		FPlane(1.164383f, 2.017232f, 0.000000f, 0.000000f),
		FPlane(0.000000f, 0.000000f, 0.000000f, 0.000000f)
	);

	const FMatrix YuvToSrgbPs4 = FMatrix(
		FPlane(1.164400f, 0.000000f, 1.792700f, 0.000000f),
		FPlane(1.164400f, -0.213300f, -0.532900f, 0.000000f),
		FPlane(1.164400f, 2.112400f, 0.000000f, 0.000000f),
		FPlane(0.000000f, 0.000000f, 0.000000f, 0.000000f)
	);

	const FMatrix YuvToSrgbRec601 = FMatrix(
		FPlane(1.000000f, 0.000000f, 1.139830f, 0.000000f),
		FPlane(1.000000f, -0.394650f, -0.580600f, 0.000000f),
		FPlane(1.000000f, 2.032110, 0.000000, 0.000000f),
		FPlane(0.000000f, 0.000000f, 0.000000f, 0.000000f)
	);

	const FMatrix YuvToRgbRec709 = FMatrix(
		FPlane(1.000000f, 0.000000f, 1.280330f, 0.000000f),
		FPlane(1.000000f, -0.214820f, -0.380590f, 0.000000f),
		FPlane(1.000000f, 2.127980f, 0.000000f, 0.000000f),
		FPlane(0.000000f, 0.000000f, 0.000000f, 0.000000f)
	);

	const FMatrix YuvToRgbRec709Full = FMatrix(
		FPlane(1.164400f, 0.000000f, 1.792700f, 0.000000f),
		FPlane(1.164400f, -0.213300f, -0.532900f, 0.000000f),
		FPlane(1.164400f, 2.112400f, 0.000000f, 0.000000f),
		FPlane(0.000000f, 0.000000f, 0.000000f, 0.000000f)
	);

	const FMatrix RgbToYuvRec709Full = FMatrix(
		FPlane(0.182581f, 0.614210f, 0.062020f, 0.000000f),
		FPlane(-0.100642f, -0.338566f, 0.439208f, 0.000000f),
		FPlane(0.439227f, -0.398944f, -0.040283f, 0.000000f),
		FPlane(0.000000f, 0.000000f, 0.000000f, 0.000000f)
	);

	const FVector YUVOffset8bits = FVector(0.06274509803921568627f, 0.5019607843137254902f, 0.5019607843137254902f);

	const FVector YUVOffset10bits = FVector(0.06256109481915933529f, 0.50048875855327468231f, 0.50048875855327468231f);

	/** Setup YUV Offset in matrix */
	FMatrix CombineColorTransformAndOffset(const FMatrix& InMatrix, const FVector& InYUVOffset)
	{
		FMatrix Result = InMatrix;
		// Offset in last column:
		// 1) to allow for 4x4 matrix multiplication optimization when going from RGB to YUV (hence the 1.0 in the [3][3] matrix location)
		// 2) stored in empty space when going from YUV to RGB
		Result.M[0][3] = InYUVOffset.X;
		Result.M[1][3] = InYUVOffset.Y;
		Result.M[2][3] = InYUVOffset.Z;
		Result.M[3][3] = 1.0f;
		return Result;
	}
}

/* FMediaShadersVS shader
 *****************************************************************************/

IMPLEMENT_SHADER_TYPE(, FYoumeVideoShadersVS, TEXT("/YoumeVideoShaders/YoumeVideo.usf"), TEXT("YoumeVertexShader"), SF_Vertex);

/* FYoumeYUVConvertPS shader
 *****************************************************************************/

IMPLEMENT_SHADER_TYPE(, FYoumeYUVConvertPS, TEXT("/YoumeVideoShaders/YoumeVideo.usf"), TEXT("YoumeYUVConvertPS"), SF_Pixel);


void FYoumeYUVConvertPS::SetParameters(FRHICommandList& CommandList, TShaderMapRef<FYoumeYUVConvertPS> PixelShader, TRefCountPtr<FRHITexture2D> YTexture, TRefCountPtr<FRHITexture2D> UTexture, TRefCountPtr<FRHITexture2D> VTexture, const FIntPoint& OutputDimensions, const FMatrix& ColorTransform, const FVector& YUVOffset, bool SrgbToLinear)
{
	FYoumeYUVConvertPS::FParameters PassParameters;

	PassParameters.ColorTransform = YoumeVideoShaders::CombineColorTransformAndOffset(ColorTransform, YUVOffset);
	PassParameters.SrgbToLinear = SrgbToLinear;
	PassParameters.YTexture = YTexture;
	PassParameters.UTexture = UTexture;
	PassParameters.VTexture = VTexture;
	PassParameters.YSampler = TStaticSamplerState<SF_Bilinear>::GetRHI();
	PassParameters.USampler = TStaticSamplerState<SF_Bilinear>::GetRHI();
	PassParameters.VSampler = TStaticSamplerState<SF_Bilinear>::GetRHI();
	PassParameters.UVScale = FVector2D((float)OutputDimensions.X / (float)YTexture->GetSizeX(), (float)OutputDimensions.Y / (float)YTexture->GetSizeY());

	SetShaderParameters(CommandList, PixelShader, PixelShader.GetPixelShader(), PassParameters);
}