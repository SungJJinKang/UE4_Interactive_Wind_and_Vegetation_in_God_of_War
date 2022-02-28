// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMap.h"


UWindMap::UWindMap()
{
	
}


bool UWindMap::InitializeWithRenderTargetOption(const int32 renderTargetWidth, const int32 renderTargetHeight, const ETextureRenderTargetFormat renderTargetForamt)
{
	bool isSuccess = false;

	ensure(IsValid(WindMapRenderTarget2D) == false);
	check(renderTargetWidth > 0 && renderTargetHeight > 0 && (renderTargetWidth & (renderTargetWidth - 1)) == 0 && (renderTargetHeight & (renderTargetHeight - 1)) == 0);

	if
	(
		IsValid(WindMapRenderTarget2D) == false &&
		renderTargetWidth > 0 && renderTargetHeight > 0 && (renderTargetWidth & (renderTargetWidth - 1)) == 0 && (renderTargetHeight & (renderTargetHeight - 1)) == 0
	)
	{
		UTextureRenderTarget2D* renderTarget2D = NewObject<UTextureRenderTarget2D>();

		check(IsValid(renderTarget2D));
		if (IsValid(renderTarget2D))
		{
			renderTarget2D->InitCustomFormat(renderTargetWidth, renderTargetHeight, GetPixelFormatFromRenderTargetFormat(renderTargetForamt), false);
			WindMapRenderTarget2D = renderTarget2D;
			isSuccess = true;
		}
	}

	return isSuccess;
}

bool UWindMap::IsWindMapRenderTarget2DCreated() const
{
	return IsValid(WindMapRenderTarget2D);
}

UTextureRenderTarget2D* UWindMap::GetWindMapRenderTarget2D()
{
	return WindMapRenderTarget2D;
}

const UTextureRenderTarget2D* UWindMap::GetWindMapRenderTarget2D() const
{
	return WindMapRenderTarget2D;
}

void UWindMap::SetStaticWindVector(const FVector4& staticWindVector)
{
	WindMapRenderTarget2D->ClearColor = FLinearColor{ staticWindVector };
}

FVector4 UWindMap::GetStaticWindVector() const
{
	FVector4 staticWindVector;

	if(IsWindMapRenderTarget2DCreated())
	{
		staticWindVector = WindMapRenderTarget2D->ClearColor;
	}
	else
	{
		staticWindVector = FVector4{ 0.0f };
	}

	return staticWindVector;
}
