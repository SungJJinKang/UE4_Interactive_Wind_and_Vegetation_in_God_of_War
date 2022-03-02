// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMapDebuggerComponent.h"

#include "GameFramework/Actor.h"
#include "WindMap.h"
#include "WindMapController.h"

// Sets default values for this component's properties
UWindMapDebuggerComponent::UWindMapDebuggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UWindMapDebuggerComponent::DrawArrowsOfDebugTargetWindMaps()
{
	for(UWindMap* windMap : DebugTargetWindMaps)
	{
		DrawArrowsOfDebugTargetWindMap(windMap);
	}
}


void UWindMapDebuggerComponent::AddDebugTargetWindMapsFromOwnerActor()
{
	TArray<UWindMapController*> windMapControllersAttachedToOwnerActor{};
	GetOwner()->GetComponents<UWindMapController>(windMapControllersAttachedToOwnerActor);
	for(UWindMapController* windMapController : windMapControllersAttachedToOwnerActor)
	{
		if(IsValid(windMapController))
		{
			const int32 ownedWindMapCount = windMapController->GetOwnedWindMapCount();
			for(int32 index = 0 ; index < ownedWindMapCount ; index++)
			{
				DebugTargetWindMaps.AddUnique(windMapController->GetOwnedWindMapByIndex(index));
			}
		}
	}
}

// Called when the game starts
void UWindMapDebuggerComponent::BeginPlay()
{
	Super::BeginPlay();

	AddDebugTargetWindMapsFromOwnerActor();
	
}


// Called every frame
void UWindMapDebuggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bTickDrawArrowsOfDebugTargetWindMaps == true)
	{
		DrawArrowsOfDebugTargetWindMaps();
	}
}

