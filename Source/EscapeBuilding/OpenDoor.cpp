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

	Owner = GetOwner();
	if (!PressurePlate) { UE_LOG(LogTemp, Error, TEXT("missing door pressureplate")) }
	if (!TriggerActor) { UE_LOG(LogTemp, Error, TEXT("missing door trigger actor")) }
	if (!Owner) { UE_LOG(LogTemp, Error, TEXT("missing door Owner?")) }
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PressurePlate) { CheckAndOpen(); }
}

void UOpenDoor::CheckAndOpen()
{
	if (!TriggerActor) { return; }
	float Seconds = GetWorld()->GetTimeSeconds();
	if (PressurePlate->IsOverlappingActor(TriggerActor)) {
		OpenDoor();
		LastOpened = Seconds;
	}
	else if (Seconds > LastOpened + CloseDelay) {
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor() {
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}
void UOpenDoor::CloseDoor() {
	Owner->SetActorRotation(FRotator(0.0f, ClosedAngle, 0.0f));
}

