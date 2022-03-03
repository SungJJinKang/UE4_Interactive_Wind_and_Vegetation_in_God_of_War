// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WindModifierComponent.generated.h"

class UWindMap;
class UMaterial;
class UMaterialInstanceDynamic;

UCLASS( ClassGroup=(WindMap), Abstract, Blueprintable, meta=(BlueprintSpawnableComponent) )
class WIND_VEGETATION_GOW4_API UWindModifierComponent : public USceneComponent
{
	GENERATED_BODY()

private:


		
protected:

	UPROPERTY(Category="WindMap", VisibleAnywhere)
	TArray<TWeakObjectPtr<UWindMap>> TargetWindMaps;

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadOnly)
	UMaterial* WindModifierMaterial;

	UPROPERTY(Category = "WindMap", VisibleAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* WindModifierMaterialInstanceDynamic;

	virtual void BeginPlay() override;

public:	

	UPROPERTY(Category = "WindMap", EditAnywhere, BlueprintReadWrite)
	bool bTickDrawWindVectorToTargetWindMaps;

	UWindModifierComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(Category = "WindMap", BlueprintImplementableEvent, BlueprintCallable, CallInEditor)
	void DrawWindVectorToPassedWindMap(UWindMap* windMap);

	UFUNCTION(Category = "WindMap", BlueprintCallable, CallInEditor)
	void DrawWindVectorToTargetWindMaps();

	UFUNCTION(Category = "WindMap", BlueprintCallable)
	void DrawWindVectorToTargetWindMapByIndex(const int32 index);

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, BlueprintCallable)
	FVector GetModifierOriginLocation();
	virtual FVector GetModifierOriginLocation_Implementation();
	
	UFUNCTION(Category = "WindMap", BlueprintPure)
	FORCEINLINE int32 GetTargetWindMapCount() const
	{
		return TargetWindMaps.Num();
	}

	UFUNCTION(Category = "WindMap", BlueprintCallable)
	FORCEINLINE UWindMap* GetTargetWindMap(const int32 targetWindMapIndex)
	{
		UWindMap* targetWindMap;

		if(TargetWindMaps.Num() > targetWindMapIndex)
		{
			targetWindMap = TargetWindMaps[targetWindMapIndex].Get();
		}
		else
		{
			targetWindMap = nullptr;
		}

		return targetWindMap;
	}


	UFUNCTION(Category = "WindMap", BlueprintCallable)
	void AddTargetWindMapTo(UWindMap* const windMap);

	UFUNCTION(Category = "WindMap", BlueprintCallable)
	void RemoveTargetWindMap(const int32 index);

	UFUNCTION(Category = "WindMap", BlueprintCallable)
	void ClearWindMap();

	UFUNCTION(Category = "WindMap", CallInEditor, BlueprintCallable)
	void SetAllCreatedWindMapToTargetWindMaps();
};
