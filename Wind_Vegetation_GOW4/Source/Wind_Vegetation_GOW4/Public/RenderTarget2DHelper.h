// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Float16ColorArrayWrapper.h"
#include "RenderTarget2DHelper.generated.h"

class UTextureRenderTarget2D;


/**
 * 
 */
UCLASS()
class WIND_VEGETATION_GOW4_API URenderTarget2DHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/// <summary>
	/// This function is really slow because Reading pixels from gpu to cpu blocks game thread until texture is avaliable
	/// But in my project, this function is called only for debug, editor visualization.
	/// </summary>
	UFUNCTION(BlueprintCallable)
	static bool ReadPixelsFromRenderTarget2D(const UTextureRenderTarget2D* const renderTarget2D, UFloat16ColorArrayWrapper* const float16ColorArrayWrapper, int32& textureWidth, int32& textureHeight);
};
