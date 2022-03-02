// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMapManager.h"
#include "WindMap.h"

UWindMap* UWindMapManager::CreateWindMap
(
	UObject* Outer, 
	const int32 renderTargetWidth, 
	const int32 renderTargetHeight, 
	const ETextureRenderTargetFormat renderTargetForamt
)
{
	UWindMap* createdWindMap = nullptr;
	
	UClass* windMapBPClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, TEXT("Blueprint'/Game/WindSystem/Helper/WindMap_BP.WindMap_BP_C'")));
	check(IsValid(windMapBPClass));
	if (IsValid(windMapBPClass))
	{
		createdWindMap = NewObject<UWindMap>(Outer, windMapBPClass);
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
				createdWindMap->InitializeWindMap();
			}
		}
	}

	return createdWindMap;
}
