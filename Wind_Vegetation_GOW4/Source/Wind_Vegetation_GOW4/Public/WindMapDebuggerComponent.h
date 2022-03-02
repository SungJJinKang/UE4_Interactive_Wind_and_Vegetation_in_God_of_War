// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WindMapDebuggerComponent.generated.h"

class UWindMap;

UCLASS( Blueprintable, meta=(BlueprintSpawnableComponent) )
class WIND_VEGETATION_GOW4_API UWindMapDebuggerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, CallInEditor)
	void AddDebugTargetWindMapsFromOwnerActor();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTickDrawArrowsOfDebugTargetWindMaps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTickDrawWindVectorTextOfDebugTargetWindMaps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UWindMap*> DebugTargetWindMaps;

	UWindMapDebuggerComponent();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DrawArrowsOfDebugTargetWindMap(const UWindMap* const windMap) const;
	UFUNCTION(BlueprintCallable)
	void DrawArrowsOfDebugTargetWindMaps();
		
};
