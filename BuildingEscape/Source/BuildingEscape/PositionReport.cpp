// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Math/Vector.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
	AActor* obj = GetOwner();
	FString objectName = GetOwner()->GetName();
	FString position = obj->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Position Report Reporting For Duty On a: %s"), *objectName);
	UE_LOG(LogTemp, Warning, TEXT("Position Report Reporting Position: %s"), *position);
	// ...
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
	// ...
}

