// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	UPROPERTY(BlueprintAssignable)
	FDoorRequest OnOpen;
	UPROPERTY(BlueprintAssignable)
	FDoorRequest OnClose;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//a pointer to that specific pressure plate
	UPROPERTY(EditAnywhere)
	ATriggerVolume *pressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float massThreshold = 50.f;

	//Self Door Object
	AActor* owner = nullptr;

	//read total mass from pressure plate (trigger volume)
	float GetTotalMassOnPlate();
	
};
