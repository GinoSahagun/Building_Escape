// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Gameframework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
	if (!pressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing Pressure Plate : Actor Name %s"), *owner->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	//Poll For Pressure Plate
	if (GetTotalMassOnPlate() > massThreshold)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}



}

float UOpenDoor::GetTotalMassOnPlate()
{
	float totalMass = 0.0f;
	TArray<AActor*> ActorsOverlapped;
	if (!pressurePlate) { return totalMass; }
	pressurePlate->GetOverlappingActors(ActorsOverlapped);
	UPrimitiveComponent* component;
	
	int len = ActorsOverlapped.Num();
	for (const auto &kv : ActorsOverlapped)
	{
		component = kv->FindComponentByClass<UPrimitiveComponent>();
		if (component)
			totalMass += component->GetMass();

	}

	return totalMass;

}

