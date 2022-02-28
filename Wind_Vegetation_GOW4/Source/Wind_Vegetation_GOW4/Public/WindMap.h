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
UCLASS(Blueprintable)
class WIND_VEGETATION_GOW4_API UWindMap : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadOnly)
	UTextureRenderTarget2D* WindMapRenderTarget2D;


public:

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	FVector WindMapOriginWorldPosition;

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	FVector WindMapOffset;

	UWindMap();
	virtual void BeginDestroy() override;
	
	UFUNCTION(BlueprintCallable)
	bool InitializeWithRenderTargetOption(const int32 renderTargetWidth, const int32 renderTargetHeight, const ETextureRenderTargetFormat renderTargetForamt);
	
	bool IsWindMapRenderTarget2DCreated() const;
	UTextureRenderTarget2D* GetWindMapRenderTarget2D();
	const UTextureRenderTarget2D* GetWindMapRenderTarget2D() const;

	UFUNCTION(BlueprintCallable)
	void SetStaticWindVector(const FVector4& staticWindVector);
	
	UFUNCTION(CallInEditor)
	void SetStaticWindVectorForTesting();

	UFUNCTION(BluePrintPure, BlueprintCallable)
	FVector4 GetStaticWindVector() const;

	UFUNCTION(BlueprintCallable)
	void ClearWindMapRenderTarget2D();
};
