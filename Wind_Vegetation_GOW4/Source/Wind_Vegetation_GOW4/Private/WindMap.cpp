// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMap.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "WindMapManager.h"

void UWindMap::ApplyPostProcessToBackBuffer()
{
	UTextureRenderTarget2D* const backRenderTarget = GetBackBufferWindMapRenderTarget2D();

	if(IsValid(backRenderTarget) && IsValid(WindMapPostProcessMaterialInstance))
	{
		UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(), backRenderTarget, WindMapPostProcessMaterialInstance);
	}
}

UWorld* UWindMap::GetWorldOfWindMap() const
{
	return GetWorld();
}

UWindMap::UWindMap()
	: StaticWindVector(0.0f), DefaultRenderTargetCount(3)
{
	//UWindMapManager::AddWindMapToManager(this);
	
}

void UWindMap::BeginDestroy()
{
	UObject::BeginDestroy();
	
	for(UTextureRenderTarget2D* renderTarget : WindMapRenderTarget2Ds)
	{
		if (IsValid(renderTarget))
		{
			renderTarget->MarkPendingKill();
		}
	}
	
}


void UWindMap::InitializeWindMap_Implementation()
{
}

bool UWindMap::InitializeWithRenderTargetOption(const int32 renderTargetWidth, const int32 renderTargetHeight, const ETextureRenderTargetFormat renderTargetForamt)
{
	bool isSuccess = false;
	
	ensure(WindMapRenderTarget2Ds.Num() == 0);
	check(renderTargetWidth > 0 && renderTargetHeight > 0 && (renderTargetWidth & (renderTargetWidth - 1)) == 0 && (renderTargetHeight & (renderTargetHeight - 1)) == 0);

	if
	(
		WindMapRenderTarget2Ds.Num() == 0 &&
		renderTargetWidth > 0 && renderTargetHeight > 0 && (renderTargetWidth & (renderTargetWidth - 1)) == 0 && (renderTargetHeight & (renderTargetHeight - 1)) == 0
	)
	{
		for(uint32 i = 0 ; i < DefaultRenderTargetCount ; i++)
		{
			UTextureRenderTarget2D* renderTarget2D = NewObject<UTextureRenderTarget2D>();

			check(IsValid(renderTarget2D));
			if (IsValid(renderTarget2D))
			{
				//renderTarget2D->mipmap
				renderTarget2D->InitCustomFormat(renderTargetWidth, renderTargetHeight, GetPixelFormatFromRenderTargetFormat(renderTargetForamt), false);
				WindMapRenderTarget2Ds.Add(renderTarget2D);
				isSuccess = true;
			}
		}
	}

	return isSuccess;
}

bool UWindMap::IsWindMapRenderTarget2DCreated() const
{
	return (WindMapRenderTarget2Ds.Num() > 0);
}

UTextureRenderTarget2D* UWindMap::GetVarianceBufferWindMapRenderTarget2D()
{
	const uint32 varianceBufferIndex = GFrameCounter % 3;
	return GetWindMapRenderTarget2D(varianceBufferIndex);
}

UTextureRenderTarget2D* UWindMap::GetBackBufferWindMapRenderTarget2D()
{
	const uint32 backBufferIndex = (GFrameCounter + 1) % 3;
	return GetWindMapRenderTarget2D(backBufferIndex);
}

UTextureRenderTarget2D* UWindMap::GetFrontBufferWindMapRenderTarget2D()
{
	const uint32 frontBufferIndex = (GFrameCounter + 2) % 3;
	return GetWindMapRenderTarget2D(frontBufferIndex);
}

UTextureRenderTarget2D* UWindMap::GetWindMapRenderTarget2D(const int32 index)
{
	UTextureRenderTarget2D* renderTarget = nullptr;

	if(index < WindMapRenderTarget2Ds.Num())
	{
		if(IsValid(WindMapRenderTarget2Ds[index]))
		{
			renderTarget = WindMapRenderTarget2Ds[index];
		}
	}

	return renderTarget;
}

const UTextureRenderTarget2D* UWindMap::GetWindMapRenderTarget2D(const int32 index) const
{
	UTextureRenderTarget2D* renderTarget = nullptr;

	if (index < WindMapRenderTarget2Ds.Num())
	{
		if (IsValid(WindMapRenderTarget2Ds[index]))
		{
			renderTarget = WindMapRenderTarget2Ds[index];
		}
	}

	return renderTarget;
}

/*
void UWindMap::ApplyPostProcessToBackBuffer()
{
	if(IsWindMapRenderTarget2DCreated() && IsValid(WindMapMaterialInstance))
	{
		UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(), GetBackBufferWindMapRenderTarget2D(), WindMapMaterialInstance);
	}
}
*/

void UWindMap::PreTickWindMap_Implementation()
{
}

void UWindMap::TickWindMap()
{
	PreTickWindMap();

	ApplyPostProcessToBackBuffer();

	PostTickWindMap();
}

void UWindMap::PostTickWindMap_Implementation()
{
	//UKismetRenderingLibrary::ClearRenderTarget2D(GetWorld(), GetVarianceBufferWindMapRenderTarget2D(), FLinearColor::Transparent);
}
