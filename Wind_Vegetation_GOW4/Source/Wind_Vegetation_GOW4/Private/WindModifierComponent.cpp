// Fill out your copyright notice in the Description page of Project Settings.


#include "WindModifierComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"

// Sets default values for this component's properties
UWindModifierComponent::UWindModifierComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> StaticWindModifierMaterial( TEXT("Material'/Game/WindSystem/Helper/HelperMaterail/WindModifierMaterial.WindModifierMaterial'") );
	ensure(StaticWindModifierMaterial.Succeeded());
	if(StaticWindModifierMaterial.Succeeded())
	{
		WindModifierMaterial = StaticWindModifierMaterial.Object;
	}
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

FVector UWindModifierComponent::GetWindVector_Implementation()
{
	return GetComponentVelocity();
}

