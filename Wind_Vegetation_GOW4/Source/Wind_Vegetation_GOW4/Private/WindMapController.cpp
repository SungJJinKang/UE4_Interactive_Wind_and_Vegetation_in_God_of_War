// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMapController.h"
#include "WindMap.h"
#include "UObject/UObjectGlobals.h"
#include "WindMapManager.h"

// Sets default values for this component's properties
UWindMapController::UWindMapController()
{
	PrimaryComponentTick.bCanEverTick = true;

	bUpdateOwnedWindMaps = true;
	bCreateWindMapWhenBeginPlay = true;

	DefualtWindMapRenderTargetResolutionWidth = 32;
	DefualtWindMapRenderTargetResolutionHeight = 64;
	DefualtWindMapRenderTargetTextureFormat = ETextureRenderTargetFormat::RTF_RGBA16f;
}


void UWindMapController::AddNewWindMap()
{
	OwnedWindMap.Add(CreateWindMapWithDefaultOption());
}

void UWindMapController::AddNewWindMapWithRenderTargetOption(const int32 renderTargetWidth, const int32 renderTargetHeight, const ETextureRenderTargetFormat renderTargetForamt)
{
	OwnedWindMap.Add(UWindMapManager::CreateWindMap(GetWorld(), renderTargetWidth, renderTargetHeight, renderTargetForamt));
}

void UWindMapController::AddWindMapTo(UWindMap* const windMap)
{
	OwnedWindMap.Add(windMap);
}

void UWindMapController::RemoveWindMap(const int32 index)
{
	if(index < OwnedWindMap.Num())
	{
		if(IsValid(OwnedWindMap[index]))
		{
			OwnedWindMap[index]->MarkPendingKill();
		}
		OwnedWindMap.RemoveAt(index);
	}
}

void UWindMapController::ClearWindMap()
{
	for(UWindMap* windMap : OwnedWindMap)
	{
		if (IsValid(windMap))
		{
			windMap->MarkPendingKill();
		}
	}
	OwnedWindMap.Reset();
}

void UWindMapController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ClearWindMap();
}

void UWindMapController::TickWindMap(UWindMap* const windMap)
{
	PreTickWindMap(windMap);

	windMap->TickWindMap();
}

void UWindMapController::PreTickWindMap_Implementation(UWindMap* windMap)
{
	UpdateWindMapData(windMap);
}

void UWindMapController::TickWindMaps()
{
	for(UWindMap* windMap : OwnedWindMap)
	{
		if(IsValid(windMap))
		{
			TickWindMap(windMap);
		}
	}
}

void UWindMapController::UpdateWindMapData(UWindMap* const windMap)
{
	//if (IsValid(windMap))
	//{
		windMap->WindMapScaleInWorldSpace = WindMapSizeInWorldSpace;
		windMap->WindMapRotationMatrix = FRotationMatrix::Make(GetWindMapRotation());
		windMap->WindMapOriginWorldPosition = GetWindMapOriginWorldPosition();
		windMap->WindMapOffsetInWorldSpace = WindMapOffsetInWorldSpace;
	//}
}

// Called when the game starts
void UWindMapController::BeginPlay()
{
	Super::BeginPlay();


	if(bCreateWindMapWhenBeginPlay == true)
	{
		AddNewWindMap();
	}
	
}

UWindMap* UWindMapController::CreateWindMapWithDefaultOption() const
{
	return UWindMapManager::CreateWindMap(GetWorld(), DefualtWindMapRenderTargetResolutionWidth, DefualtWindMapRenderTargetResolutionHeight, DefualtWindMapRenderTargetTextureFormat);
}


// Called every frame
void UWindMapController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bUpdateOwnedWindMaps == true)
	{
		TickWindMaps();
	}

	ensure(WindMapSizeInWorldSpace.X > 0.0f && WindMapSizeInWorldSpace.Y > 0.0f && WindMapSizeInWorldSpace.Z > 0.0f);
	
}

FVector UWindMapController::GetWindMapOriginWorldPosition_Implementation() const
{
	return GetComponentLocation();
}

FRotator UWindMapController::GetWindMapRotation_Implementation() const
{
	return GetComponentRotation();
}
