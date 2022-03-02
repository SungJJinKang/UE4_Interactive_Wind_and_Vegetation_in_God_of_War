// Fill out your copyright notice in the Description page of Project Settings.


#include "RenderTarget2DHelper.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture.h"

bool URenderTarget2DHelper::ReadPixelsFromRenderTarget2D(const UTextureRenderTarget2D* const renderTarget2D, UFloat16ColorArrayWrapper* const float16ColorArrayWrapper, int32& textureWidth, int32& textureHeight)
{
	check(IsValid(float16ColorArrayWrapper));

	bool isSuccess = false;

	if(IsValid(renderTarget2D))
	{
		FTextureRenderTarget2DResource* textureResource = static_cast<FTextureRenderTarget2DResource*>(renderTarget2D->Resource);
		if(textureResource != nullptr)
		{
			if (textureResource->ReadFloat16Pixels(float16ColorArrayWrapper->Array, ECubeFace::CubeFace_MAX))
			{
				textureWidth = textureResource->GetSizeX();
				textureHeight = textureResource->GetSizeY();

				isSuccess = true;
			}
		}
	}

	return isSuccess;	
}