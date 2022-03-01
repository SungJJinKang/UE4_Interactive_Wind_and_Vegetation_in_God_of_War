// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMap.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "WindMapManager.h"

UWindMap::UWindMap()
	: StaticWindVectorVariance(0.0f), WindMapMaterialInstance(nullptr)
{
	//UWindMapManager::AddWindMapToManager(this);
}

void UWindMap::BeginDestroy()
{
	UObject::BeginDestroy();

	UWindMapManager::RemoveWindMapFromManager(this);
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
			//renderTarget2D->mipmap
			renderTarget2D->InitCustomFormat(renderTargetWidth, renderTargetHeight, GetPixelFormatFromRenderTargetFormat(renderTargetForamt), false);
			WindMapRenderTarget2D = renderTarget2D;
			isSuccess = true;
		}
	}

	return isSuccess;
}

void UWindMap::InitializeWindMapMaterial(UMaterial* const material)
{
	ensure(IsValid(WindMapMaterialInstance) == false && IsValid(material) == true);
	if(IsValid(WindMapMaterialInstance) == false && IsValid(material) == true)
	{
		WindMapMaterialInstance = UMaterialInstanceDynamic::Create(material, this);
		check(WindMapMaterialInstance);
	}
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
	if (IsWindMapRenderTarget2DCreated())
	{
		WindMapRenderTarget2D->ClearColor = FLinearColor{ staticWindVector };
	}
}

void UWindMap::SetStaticWindVectorForTesting()
{
	SetStaticWindVector(FVector4(1.0f, 0.0f, 1.0f, 1.0f));
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

void UWindMap::ClearWindMapRenderTarget2D()
{
	if(IsWindMapRenderTarget2DCreated())
	{
		UKismetRenderingLibrary::ClearRenderTarget2D(GetWorld(), WindMapRenderTarget2D, WindMapRenderTarget2D->ClearColor);
	}
}

void UWindMap::DrawWindMapMaterialInstanceToWindMapRenderTarget()
{
	if(IsValid(WindMapRenderTarget2D) && IsValid(WindMapMaterialInstance))
	{
		UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(), WindMapRenderTarget2D, WindMapMaterialInstance);
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