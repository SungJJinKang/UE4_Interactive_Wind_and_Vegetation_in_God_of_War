// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMapController.h"
#include "WindMap.h"
#include "UObject/UObjectGlobals.h"

// Sets default values for this component's properties
UWindMapController::UWindMapController()
{
	PrimaryComponentTick.bCanEverTick = true;

	bCreateWindMapWhenBeginPlay = true;

	TargetWindMapWidth = 256;
	TargetWindMapHeight = 512;
	TargetWindMapTextureRenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA32f;
	WindMapWorldOffset = FVector(0.0f);
}


void UWindMapController::AddNewWindMap()
{
	OwnedWindMap.Add(CreateWindMap());
}

void UWindMapController::AddNewWindMapWithRenderTargetOption(const int32 renderTargetWidth, const int32 renderTargetHeight, const ETextureRenderTargetFormat renderTargetForamt)
{
	OwnedWindMap.Add(CreateWindMap(renderTargetWidth, renderTargetHeight, renderTargetForamt));
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
			ownedWindMap->UpdateWindMapOriginWorldPosition(GetComponentLocation() + WindMapWorldOffset);
		}
	}
}

UWindMap* UWindMapController::CreateWindMap()
{
	return CreateWindMap(TargetWindMapWidth, TargetWindMapHeight, TargetWindMapTextureRenderTargetFormat);
}

UWindMap* UWindMapController::CreateWindMap(const int32 renderTargetWidth, const int32 renderTargetHeight, const ETextureRenderTargetFormat renderTargetForamt)
{
	UWindMap* createdWindMap = NewObject<UWindMap>();
	check(IsValid(createdWindMap));
	if (IsValid(createdWindMap))
	{
		if(createdWindMap->InitializeWithRenderTargetOption(renderTargetWidth, renderTargetHeight, renderTargetForamt) == false)
		{
			ensure(false);
			createdWindMap->MarkPendingKill();
			createdWindMap = nullptr;
		}
	}

	return createdWindMap;
}


// Called every frame
void UWindMapController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateWindMapOriginWorldPosition();
}

