// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WindMap.generated.h"

class UTextureRenderTarget2D;

/**
 * 
 */
UCLASS(BlueprintType)
class WIND_VEGETATION_GOW4_API UWindMap : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	UTextureRenderTarget2D* WindMap;

public:

	UFUNCTION(Category = "WindMap", BlueprintCallable)
	void SlowUpdateWindMap(const FVector& localLocation, const FVector& windVector);

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	FVector StaticWindVector;
};
