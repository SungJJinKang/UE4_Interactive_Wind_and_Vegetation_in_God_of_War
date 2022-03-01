// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMap.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "WindMapManager.h"

UWindMap::UWindMap()
	: StaticWindVector(0.0f), DefaultRenderTargetCount(2), WindMapMaterialInstance(nullptr)
{
	//UWindMapManager::AddWindMapToManager(this);
	
}

void UWindMap::BeginDestroy()
{
	UObject::BeginDestroy();
	
	if(IsValid(WindMapMaterialInstance))
	{
		WindMapMaterialInstance->MarkPendingKill();
	}

	for(UTextureRenderTarget2D* renderTarget : WindMapRenderTarget2Ds)
	{
		if (IsValid(renderTarget))
		{
			renderTarget->MarkPendingKill();
		}
	}
	
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

void UWindMap::InitializeWindMapMaterialWithDefaultMaterial()
{
	ensure(IsValid(WindMapMaterialInstance) == false);
	if (IsValid(WindMapMaterialInstance) == false)
	{
		UMaterial* const windMapMaterial = LoadObject<UMaterial>(this, TEXT("Material'/Game/WindSystem/Helper/HelperMaterail/WindMapPostProcessMaterial.WindMapPostProcessMaterial'"));
		check(IsValid(windMapMaterial));
		if (IsValid(windMapMaterial))
		{
			InitializeWindMapMaterial(windMapMaterial);
		}
	}
}

void UWindMap::InitializeWindMapMaterial(UMaterial* const material)
{
	ensure(IsValid(WindMapMaterialInstance) == false && IsValid(material) == true);
	if (IsValid(WindMapMaterialInstance) == false && IsValid(material) == true)
	{
		WindMapMaterialInstance = UMaterialInstanceDynamic::Create(material, this);
		check(IsValid(WindMapMaterialInstance));
	}
}

bool UWindMap::IsWindMapRenderTarget2DCreated() const
{
	return (WindMapRenderTarget2Ds.Num() > 0);
}

UTextureRenderTarget2D* UWindMap::GetBackBufferWindMapRenderTarget2D()
{
	const uint32 backBufferIndex = GFrameCounter % 2;
	return GetWindMapRenderTarget2D(backBufferIndex);
}

UTextureRenderTarget2D* UWindMap::GetFrontBufferWindMapRenderTarget2D()
{
	const uint32 frontBufferIndex = (GFrameCounter + 1) % 2;
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

void UWindMap::DrawWindMapMaterialInstanceToWindMapRenderTarget()
{
	if(IsWindMapRenderTarget2DCreated() && IsValid(WindMapMaterialInstance))
	{
		
		UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(), GetFrontBufferWindMapRenderTarget2D(), WindMapMaterialInstance);
	}
}

void UWindMap::PreTickWindMap_Implementation()
{
}

void UWindMap::TickWindMap()
{
	PreTickWindMap();

	DrawWindMapMaterialInstanceToWindMapRenderTarget();
}