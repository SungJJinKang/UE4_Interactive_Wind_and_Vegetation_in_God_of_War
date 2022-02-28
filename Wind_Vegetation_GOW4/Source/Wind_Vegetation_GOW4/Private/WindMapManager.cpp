// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMapManager.h"
#include "WindMap.h"

TArray<UWindMap*> UWindMapManager::CreatedWindMaps{};

void UWindMapManager::AddWindMapToManager(UWindMap* const windMap)
{
	CreatedWindMaps.Add(windMap);
}

void UWindMapManager::RemoveWindMapFromManager(UWindMap* const windMap)
{
	CreatedWindMaps.Remove(windMap);
}

TArray<UWindMap*>& UWindMapManager::GetCreatedWindMaps()
{
	return CreatedWindMaps;
}

UWindMap* UWindMapManager::CreateWindMap(UObject* Outer, const int32 renderTargetWidth, const int32 renderTargetHeight, const ETextureRenderTargetFormat renderTargetForamt)
{
	UWindMap* createdWindMap = NewObject<UWindMap>(Outer);
	check(IsValid(createdWindMap));
	if (IsValid(createdWindMap))
	{
		if (createdWindMap->InitializeWithRenderTargetOption(renderTargetWidth, renderTargetHeight, renderTargetForamt) == false)
		{
			ensure(false);
			createdWindMap->MarkPendingKill();
			createdWindMap = nullptr;
		}
		else
		{
			AddWindMapToManager(createdWindMap);
		}
	}

	return createdWindMap;
}
