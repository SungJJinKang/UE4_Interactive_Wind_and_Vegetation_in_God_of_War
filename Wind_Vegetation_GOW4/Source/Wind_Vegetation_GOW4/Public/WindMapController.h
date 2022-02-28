// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "WindMapController.generated.h"

class UWindMap;

UCLASS( ClassGroup=(WindMap), Blueprintable, meta=(BlueprintSpawnableComponent) )
class WIND_VEGETATION_GOW4_API UWindMapController : public USceneComponent
{
	GENERATED_BODY()

private:

	void UpdateWindMapOriginWorldPosition();
	UWindMap* CreateWindMap();
	UWindMap* CreateWindMap(const int32 renderTargetWidth, const int32 renderTargetHeight, const ETextureRenderTargetFormat renderTargetForamt);
		
protected:

	UPROPERTY(EditDefaultsOnly)
	int32 TargetWindMapWidth;

	UPROPERTY(EditDefaultsOnly)
	int32 TargetWindMapHeight;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ETextureRenderTargetFormat> TargetWindMapTextureRenderTargetFormat;

	UPROPERTY(EditDefaultsOnly)
	bool bCreateWindMapWhenBeginPlay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UWindMap*> OwnedWindMap;

public:

	UPROPERTY(BlueprintReadWrite)
	FVector WindMapWorldOffset;

	UWindMapController();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UWindMap* GetOwnedWindMap();

	UFUNCTION(BlueprintCallable)
	void AddNewWindMap();

	UFUNCTION(BlueprintCallable)
	void AddNewWindMapWithRenderTargetOption(const int32 renderTargetWidth, const int32 renderTargetHeight, const ETextureRenderTargetFormat renderTargetForamt);

	UFUNCTION(BlueprintCallable)
	void AddWindMapTo(UWindMap* const windMap);

	UFUNCTION(BlueprintCallable)
	void RemoveWindMap(const int32 index);

	UFUNCTION(BlueprintCallable)
	void ClearWindMap();
};
