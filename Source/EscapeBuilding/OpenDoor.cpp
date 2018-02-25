// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Gameframework/Actor.h"


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

	//This is just for testing, replace with statue later
	AActor* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	TriggerActor = PlayerPawn;



}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(TriggerActor)) {
		OpenDoor();
	} else {
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor() {
	//get owner
	AActor* Owner = GetOwner();
	//create rotator
	FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);
	//set rotation
	Owner->SetActorRotation(NewRotation);
}
void UOpenDoor::CloseDoor() {
	//get owner
	AActor* Owner = GetOwner();
	//create rotator
	FRotator NewRotation = FRotator(0.0f, ClosedAngle, 0.0f);
	//set rotation
	Owner->SetActorRotation(NewRotation);
}

