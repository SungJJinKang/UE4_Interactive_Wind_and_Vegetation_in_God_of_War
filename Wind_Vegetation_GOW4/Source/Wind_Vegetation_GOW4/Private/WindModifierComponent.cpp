// Fill out your copyright notice in the Description page of Project Settings.


#include "WindModifierComponent.h"
#include "WindMap.h"
#include "UObject/UObjectIterator.h"

// Sets default values for this component's properties
UWindModifierComponent::UWindModifierComponent()
	: bTickDrawWindVectorToTargetWindMaps(false)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
}


// Called when the game starts
void UWindModifierComponent::BeginPlay()
{
	Super::BeginPlay();

	SetAllCreatedWindMapToTargetWindMaps();
	
}


// Called every frame
void UWindModifierComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bTickDrawWindVectorToTargetWindMaps)
	{
		DrawWindVectorToTargetWindMaps();
	}
	
}

FVector UWindModifierComponent::GetModifierOriginLocation_Implementation()
{
	return GetComponentLocation();
}

/*
FVector UWindModifierComponent::GetWindVector_Implementation()
{
	return GetComponentVelocity();
}
*/

void UWindModifierComponent::AddTargetWindMapTo(UWindMap* const windMap)
{
	if
	(
		IsValid(windMap) && 
		TargetWindMaps.ContainsByPredicate([windMap](const TWeakObjectPtr<UWindMap>& weakWindMap) { return weakWindMap.Get() == windMap; }) == false
	)
	{
		TargetWindMaps.Add(windMap);
	}
}

void UWindModifierComponent::RemoveTargetWindMap(const int32 index)
{
	if(index < TargetWindMaps.Num())
	{
		TargetWindMaps.RemoveAt(index);
	}
}

void UWindModifierComponent::ClearWindMap()
{
	TargetWindMaps.Reset();
}

void UWindModifierComponent::SetAllCreatedWindMapToTargetWindMaps()
{
	for (TObjectIterator<UWindMap> Itr; Itr; ++Itr)
	{
		AddTargetWindMapTo(*Itr);
	}
}
