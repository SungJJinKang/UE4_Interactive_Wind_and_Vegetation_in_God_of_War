// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WindModifierComponent.generated.h"

class UWindMap;
class UMaterial;

UCLASS( ClassGroup=(WindMap), Blueprintable, meta=(BlueprintSpawnableComponent) )
class WIND_VEGETATION_GOW4_API UWindModifierComponent : public USceneComponent
{
	GENERATED_BODY()

private:


		
protected:

	UPROPERTY(Category="WindMap", BlueprintReadWrite)
	TArray<UWindMap*> TargetWindMaps;

	UPROPERTY(Category = "WindMap", BlueprintReadOnly)
	UMaterial* WindModifierMaterial;

	virtual void BeginPlay() override;
	
public:	

	UWindModifierComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool DrawVelocityToTargetWindMaps();

	UFUNCTION(BlueprintNativeEvent)
	FVector GetVelocity();
	virtual FVector GetVelocity_Implementation();
};
