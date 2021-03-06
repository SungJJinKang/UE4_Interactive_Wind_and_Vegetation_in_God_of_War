// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "WindMapController.generated.h"

class UWindMap;
class UMaterial;

UCLASS( ClassGroup=(WindMap), Abstract, Blueprintable, meta=(BlueprintSpawnableComponent) )
class WIND_VEGETATION_GOW4_API UWindMapController : public USceneComponent
{
	GENERATED_BODY()

private:
	
	UWindMap* CreateWindMapWithDefaultOption() const;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterial* WindMapMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DefualtWindMapRenderTargetResolutionWidth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DefualtWindMapRenderTargetResolutionHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 DefualtWindMapRenderTargetResolutionDepth;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ETextureRenderTargetFormat> DefualtWindMapRenderTargetTextureFormat;

	UPROPERTY(EditDefaultsOnly)
	bool bCreateWindMapWhenBeginPlay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UWindMap*> OwnedWindMap;

	UFUNCTION()
	void TickWindMap(UWindMap* const windMap);
	
	UFUNCTION()
	void TickWindMaps();
	
	UFUNCTION()
	void UpdateWindMapData(UWindMap* const windMap);


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUpdateOwnedWindMaps;
	
	UWindMapController();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void AddNewWindMap();

	UFUNCTION(BlueprintCallable)
	void AddNewWindMapWithRenderTargetOption
	(
		const int32 renderTargetWidth, 
		const int32 renderTargetHeight, 
		const int32 renderTargetDepth, 
		const ETextureRenderTargetFormat renderTargetForamt
	);

	UFUNCTION(BlueprintCallable)
	void AddWindMapTo(UWindMap* const windMap);

	UFUNCTION(BlueprintCallable)
	void RemoveWindMap(const int32 index);

	UFUNCTION(BlueprintCallable)
	void ClearWindMap();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, BlueprintCallable)
	FVector GetWindMapOriginWorldPosition() const;
	virtual FVector GetWindMapOriginWorldPosition_Implementation() const;
	
	UFUNCTION(BlueprintPure, BlueprintNativeEvent, BlueprintCallable)
	FRotator GetWindMapRotation() const;
	virtual FRotator GetWindMapRotation_Implementation() const;

	UFUNCTION(BlueprintCallable)
	UWindMap* GetOwnedWindMapByIndex(const int32 index);
	UFUNCTION(BlueprintCallable)
	int32 GetOwnedWindMapCount() const;
};
