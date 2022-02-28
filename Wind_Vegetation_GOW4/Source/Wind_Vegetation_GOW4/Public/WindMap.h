// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/TextureRenderTarget2D.h"

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
	UTextureRenderTarget2D* WindMapRenderTarget2D;

	UPROPERTY(Category = "WindMap", BlueprintReadOnly)
	FVector WindMapOriginWorldPosition;

public:

	UWindMap();

	UFUNCTION(BlueprintCallable)
	void Initialize();
	UFUNCTION(BlueprintCallable)
	void InitializeWithRenderTargetOption(const int32 renderTargetWidth, const int32 renderTargetHeight, const ETextureRenderTargetFormat renderTargetForamt);
	
	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	FVector StaticWindVector;

	void UpdateWindMapOriginWorldPosition(const FVector& originWorldPos);

	bool IsWindMapRenderTarget2DCreated() const;
	UTextureRenderTarget2D* GetWindMapRenderTarget2D();
	const UTextureRenderTarget2D* GetWindMapRenderTarget2D() const;
};
