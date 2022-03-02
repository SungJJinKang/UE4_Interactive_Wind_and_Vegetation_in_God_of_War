// Fill out your copyright notice in the Description page of Project Settings.


#include "RenderTarget2DHelper.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture.h"

bool URenderTarget2DHelper::ReadPixelsFromRenderTarget2D(const UTextureRenderTarget2D* const renderTarget2D, TArray<FColor>& pixels, int32& textureWidth, int32& textureHeight)
{
	bool isSuccess = false;

	if(IsValid(renderTarget2D))
	{
		FTextureRenderTarget2DResource* textureResource = static_cast<FTextureRenderTarget2DResource*>(renderTarget2D->Resource);
		if(textureResource != nullptr)
		{
			pixels.Reset();
			if (textureResource->ReadPixels(pixels))
			{
				textureWidth = textureResource->GetSizeX();
				textureHeight = textureResource->GetSizeY();

				isSuccess = true;
			}
		}
	}

	return isSuccess;	
}