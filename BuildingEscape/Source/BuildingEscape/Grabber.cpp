// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();

	findPhysicsHandleComponent();

	SetUpInputComponent();

	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	///If Phyiscs Handler does have an item
	///Then we need to move item alongside
	if (physicsHandler->GrabbedComponent)
	{
		physicsHandler->SetTargetLocation(GetLineTraceEnd());
	}


	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Display, TEXT("Trying To Reach For that Item"));

	//Ray-Cast to Reach distance
	//UE_LOG(LogTemp, Warning, TEXT("Player View %s , Rotate View %s "),*viewOut.ToString(), *rotateOut.ToString())
	

	FHitResult hit = GetFirstPhyiscsBody();
	auto component = hit.GetComponent();
	AActor *ActorHitByTrace = hit.GetActor();
	if (ActorHitByTrace)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hitting"));
		physicsHandler->GrabComponent(
			component,
			NAME_None,
			component->GetOwner()->GetActorLocation(),
			true ///Allow Rotation
		);
	}

	//TODO Attach Physics Handler
	// ...
}

void UGrabber::Release()
{
	//TODO Release PHyisc Handler
	physicsHandler->ReleaseComponent();
	UE_LOG(LogTemp, Display, TEXT("Released The Item"));
}

void UGrabber::findPhysicsHandleComponent()
{
	/// Find the Phyiscs Handler
	physicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandler == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Component Found, %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetUpInputComponent()
{
	input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (input)
	{
		input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Input Component Found, %s"), *GetOwner()->GetName());
	}
}

const FHitResult UGrabber::GetFirstPhyiscsBody()
{
	FHitResult hit;
	FCollisionQueryParams traceParams(TEXT(""), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		hit,
		GetLineTraceStart(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParams
	);
	return hit;
}

const FVector UGrabber::GetLineTraceEnd()
{
	FVector viewOut;
	FRotator rotateOut;
	FHitResult hit;
	PlayerController->GetPlayerViewPoint(viewOut, rotateOut);
	return viewOut + rotateOut.Vector() * reach;
	
}

const FVector UGrabber::GetLineTraceStart()
{
	FVector viewOut;
	FRotator rotateOut;
	FHitResult hit;
	PlayerController->GetPlayerViewPoint(viewOut, rotateOut);
	return viewOut;
}



