// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WindMapManager.generated.h"

class UWindMap;
/**
 * 
 */
UCLASS()
class WIND_VEGETATION_GOW4_API UWindMapManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	
	static TArray<UWindMap*> CreatedWindMaps;

public:

	UFUNCTION(BlueprintCallable)
	static void AddWindMapToManager(UWindMap* const windMap);

	UFUNCTION(BlueprintCallable)
	static void RemoveWindMapFromManager(UWindMap* const windMap);

	UFUNCTION(BlueprintCallable)
	static TArray<UWindMap*>& GetCreatedWindMaps();

	UFUNCTION(BlueprintCallable)
	static UWindMap* CreateWindMap
	(
		UObject* Outer,
		const int32 renderTargetWidth, 
		const int32 renderTargetHeight,
		const ETextureRenderTargetFormat renderTargetForamt,
		UMaterial* const windMapMaterial = nullptr
	);
};
