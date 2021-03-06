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

public:

	UFUNCTION(BlueprintCallable)
	static UWindMap* CreateWindMap
	(
		UObject* Outer,
		const int32 renderTargetWidth, 
		const int32 renderTargetHeight,
		const int32 renderTargetDepth,
		const ETextureRenderTargetFormat renderTargetForamt
	);
};
