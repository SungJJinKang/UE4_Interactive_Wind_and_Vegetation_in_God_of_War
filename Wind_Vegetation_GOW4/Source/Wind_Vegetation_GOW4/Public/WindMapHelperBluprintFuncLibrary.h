// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WindMapHelperBluprintFuncLibrary.generated.h"

class UWindMap;

/**
 * 
 */
UCLASS()
class WIND_VEGETATION_GOW4_API UWindMapHelperBluprintFuncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, BlueprintCallable)
	static TArray<UWindMap*> GetAllCreatedWindMap();
};
