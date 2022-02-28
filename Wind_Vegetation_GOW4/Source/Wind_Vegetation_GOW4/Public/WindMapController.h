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
	UWindMap* CreateWindMapWithDefaultOption() const;

protected:

	UPROPERTY(EditDefaultsOnly)
	int32 DefualtTargetWindMapWidth;

	UPROPERTY(EditDefaultsOnly)
	int32 DefualtTargetWindMapHeight;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ETextureRenderTargetFormat> DefualtTargetWindMapTextureRenderTargetFormat;

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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ClearColorOwnedWindMap();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
