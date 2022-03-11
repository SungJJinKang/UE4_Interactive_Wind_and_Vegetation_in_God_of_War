// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/TextureRenderTarget2D.h"

#include "WindMap.generated.h"

class UTextureRenderTarget2D;
class UMaterial;
class UMaterialInterface;
class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS(Blueprintable)
class WIND_VEGETATION_GOW4_API UWindMap : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	uint32 DefaultRenderTargetCount;

	UPROPERTY(Category = "WindMap", VisibleAnywhere, BlueprintReadOnly)
	TArray<UTextureRenderTarget2D*> WindMapRenderTarget2Ds;
	
	UPROPERTY(Category = "WindMap", VisibleAnywhere, BlueprintReadOnly)
	int32 WindMapRenderTargetDepth;
	
	UPROPERTY(Category = "WindMap", VisibleAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* WindMapPostProcessMaterialInstance;

	UPROPERTY(Category = "WindMap", VisibleAnywhere, BlueprintReadOnly)
	FVector PreviousTickWindMapOriginWorldPosition;

	UPROPERTY(Category = "WindMap", VisibleAnywhere, BlueprintReadOnly)
	FVector2D RenderTargetResolution;

	UFUNCTION()
	void ApplyPostProcessToBackBuffer();

public:

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	FVector WindMapScaleInWorldSpace;

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	FMatrix WindMapRotationMatrix;

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	FVector WindMapOriginWorldPosition;

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	FVector WindMapOffsetInWorldSpace;
	
	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	FVector StaticWindVector;

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	FVector SpeedToStaticWindVector;

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	FVector MinWindVector;

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	FVector MaxWindVector;

	UWindMap();
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintNativeEvent)
	void InitializeWindMap();
	virtual void InitializeWindMap_Implementation();
	
	UFUNCTION(BlueprintCallable)
	bool InitializeWithRenderTargetOption
	(
		const int32 renderTargetWidth,
		const int32 renderTargetHeight, 
		const int32 renderTargetDepth, 
		const ETextureRenderTargetFormat renderTargetForamt
	);
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsWindMapRenderTarget2DCreated() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UTextureRenderTarget2D* GetVarianceBufferWindMapRenderTarget2D();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UTextureRenderTarget2D* GetBackBufferWindMapRenderTarget2D();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UTextureRenderTarget2D* GetFrontBufferWindMapRenderTarget2D();
	UTextureRenderTarget2D* GetWindMapRenderTarget2D(const int32 index);
	const UTextureRenderTarget2D* GetWindMapRenderTarget2D(const int32 index) const;
	
	UFUNCTION(BlueprintNativeEvent)
	void PreTickWindMap();
	virtual void PreTickWindMap_Implementation();

	UFUNCTION(BlueprintCallable)
	void TickWindMap();


	UFUNCTION(BlueprintNativeEvent)
	void PostTickWindMap();
	virtual void PostTickWindMap_Implementation();
};
