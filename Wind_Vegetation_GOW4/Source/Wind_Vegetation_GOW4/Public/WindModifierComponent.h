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

	UWindModifierComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool DrawVelocityToTargetWindMaps();


	UFUNCTION(BlueprintPure, BlueprintNativeEvent, BlueprintCallable)
	FVector GetModifierOriginLocation();
	virtual FVector GetModifierOriginLocation_Implementation();
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetTargetWindMapCount() const
	{
		return TargetWindMaps.Num();
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetTargetWindMap(const int32 targetWindMapIndex, UWindMap*& outWindMap)
	{
		if(TargetWindMaps.Num() > targetWindMapIndex)
		{
			outWindMap = TargetWindMaps[targetWindMapIndex].Get();
			return true;
		}
		else
		{
			return false;
		}
	}

	UFUNCTION(BlueprintCallable)
	void AddTargetWindMapTo(UWindMap* const windMap);

	UFUNCTION(BlueprintCallable)
	void RemoveTargetWindMap(const int32 index);

	UFUNCTION(BlueprintCallable)
	void ClearWindMap();

	UFUNCTION(Category = "WindMap", CallInEditor, BlueprintCallable)
	void SetAllCreatedWindMapToTargetWindMaps();
};
