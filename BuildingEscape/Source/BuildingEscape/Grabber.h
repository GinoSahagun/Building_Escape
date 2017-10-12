// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	APlayerController* PlayerController = nullptr;

	UPROPERTY(EditAnywhere)
	float reach = 100.f;
		
	UPhysicsHandleComponent *physicsHandler = nullptr;

	UInputComponent *input = nullptr;

	//Ray-Cast (Line-trace) and Grab whats in Reach
	void Grab();

	//Release the object After button is no-longer being held
	void Release();

	//Find Phyiscs Handle Component
	void findPhysicsHandleComponent();

	//SetUp (Assumed) Input Component 
	void SetUpInputComponent();

	//First Hit of a Physics Body
	const FHitResult GetFirstPhyiscsBody();

	//Get Current Line Trace End (Reach Line)
	const FVector GetLineTraceEnd();

	const FVector GetLineTraceStart();

};
