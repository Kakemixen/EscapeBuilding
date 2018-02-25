// Fill out your copyright notice in the Description page of Project Settings.

#include "ShelfController.h"


// Sets default values for this component's properties
UShelfController::UShelfController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShelfController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UShelfController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume every frame
	if (PressurePlate->IsOverlappingActor(TriggerActor)) {
		LowerShelf();
	}
}

void UShelfController::LowerShelf() {
	AActor* Owner = GetOwner();
	FVector Location = Owner->GetActorLocation();
	Location.Z = 80.0f;

	Owner->SetActorLocation(Location, false);
}

