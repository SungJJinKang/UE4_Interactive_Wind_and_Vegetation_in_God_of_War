// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/TextureRenderTarget2D.h"

#include "WindMap.generated.h"

class UTextureRenderTarget2D;
class UMaterial;
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

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadOnly)
	UMaterialInstanceDynamic* WindMapMaterialInstance;


	UFUNCTION(BlueprintCallable)
	void DrawWindMapMaterialInstanceToWindMapRenderTarget();


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

	UWindMap();
	virtual void BeginDestroy() override;
	
	UFUNCTION(BlueprintCallable)
	bool InitializeWithRenderTargetOption(const int32 renderTargetWidth, const int32 renderTargetHeight, const ETextureRenderTargetFormat renderTargetForamt);

	UFUNCTION(BlueprintCallable)
	void InitializeWindMapMaterialWithDefaultMaterial();
	UFUNCTION(BlueprintCallable)
	void InitializeWindMapMaterial(UMaterial* const material);

	bool IsWindMapRenderTarget2DCreated() const;
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
};
