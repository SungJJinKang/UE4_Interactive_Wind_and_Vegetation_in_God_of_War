// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMap.h"


UWindMap::UWindMap()
{
	
}

void UWindMap::Initialize()
{
}


void UWindMap::InitializeWithRenderTargetOption(const int32 renderTargetWidth, const int32 renderTargetHeight, const ETextureRenderTargetFormat renderTargetForamt)
{
	ensure(IsValid(WindMapRenderTarget2D) == false);

	if(IsValid(WindMapRenderTarget2D) == false)
	{
		UTextureRenderTarget2D* renderTarget2D = NewObject<UTextureRenderTarget2D>();

		check(IsValid(renderTarget2D));
		if (IsValid(renderTarget2D))
		{
			renderTarget2D->InitCustomFormat(renderTargetWidth, renderTargetHeight, GetPixelFormatFromRenderTargetFormat(renderTargetForamt), false);
			WindMapRenderTarget2D = renderTarget2D;
		}
	}
}


void UWindMap::UpdateWindMapOriginWorldPosition(const FVector& originWorldPos)
{
	WindMapOriginWorldPosition = originWorldPos;
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
