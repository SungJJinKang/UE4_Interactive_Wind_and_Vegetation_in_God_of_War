// Fill out your copyright notice in the Description page of Project Settings.


#include "WindModifierComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "WindMap.h"
#include "WindMapManager.h"

// Sets default values for this component's properties
UWindModifierComponent::UWindModifierComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UWindModifierComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWindModifierComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawVelocityToTargetWindMaps();
}

FVector UWindModifierComponent::GetModifierOriginLocation_Implementation()
{
	return GetComponentLocation();
}

FVector UWindModifierComponent::GetWindVector_Implementation()
{
	return FVector{};
}



/*
FVector UWindModifierComponent::GetWindVector_Implementation()
{
	return GetComponentVelocity();
}
*/

void UWindModifierComponent::AddTargetWindMapTo(UWindMap* const windMap)
{
	if(IsValid(windMap))
	{
		TargetWindMaps.AddUnique(windMap);
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
	for(UWindMap* windMap : UWindMapManager::GetCreatedWindMaps())
	{
		AddTargetWindMapTo(windMap);
	}
}
