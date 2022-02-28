// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMapController.h"
#include "WindMap.h"
#include "UObject/UObjectGlobals.h"
#include "WindMapManager.h"

// Sets default values for this component's properties
UWindMapController::UWindMapController()
{
	PrimaryComponentTick.bCanEverTick = true;

	bCreateWindMapWhenBeginPlay = true;

	DefualtTargetWindMapWidth = 256;
	DefualtTargetWindMapHeight = 512;
	DefualtTargetWindMapTextureRenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA16f;
	WindMapWorldOffset = FVector(0.0f);
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
		windMap->MarkPendingKill();
	}
	OwnedWindMap.Reset();
}

void UWindMapController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ClearWindMap();
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


void UWindMapController::UpdateWindMapOriginWorldPosition()
{
	for(UWindMap* ownedWindMap : OwnedWindMap)
	{
		if (IsValid(ownedWindMap))
		{
			ownedWindMap-> WindMapOriginWorldPosition = GetComponentLocation() + WindMapWorldOffset;
		}
	}
}

UWindMap* UWindMapController::CreateWindMapWithDefaultOption() const
{
	return UWindMapManager::CreateWindMap(GetWorld(), DefualtTargetWindMapWidth, DefualtTargetWindMapHeight, DefualtTargetWindMapTextureRenderTargetFormat);
}


// Called every frame
void UWindMapController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateWindMapOriginWorldPosition();
}

