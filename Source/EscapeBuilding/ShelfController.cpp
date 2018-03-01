// Fill out your copyright notice in the Description page of Project Settings.

#include "ShelfController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

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
	//This is just for testing, replace with couch when you can move it
	//UWorld* World = GetWorld();
	//AController* Controller = World->GetFirstPlayerController();
	AActor* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PressurePlate1) { UE_LOG(LogTemp, Error, TEXT("missing outer pressureplate")) }
	if (!PressurePlate2) { UE_LOG(LogTemp, Error, TEXT("missing inner pressureplate")) }
	
}


// Called every frame
void UShelfController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume every frame
	if (GetTotalMassOnPlate1() > MassThreshold1) {
		if (GetTotalMassOnPlate2() > MassThreshold2_min && GetTotalMassOnPlate2() < MassThreshold2_max) {
			RaiseObject();
		}
		else {
			LowerObject();
		}
	}
	else {
		LowerObject();
	}
}

void UShelfController::LowerObject() {
	if (!up) { return; }
	up = false;
	AActor* Owner = GetOwner();
	FVector Location = Owner->GetActorLocation();
	Location.Z = LoweredHeight;

	Owner->SetActorLocation(Location, false);
}

void UShelfController::RaiseObject() {
	if (up) { return; }
	up = true;
	AActor* Owner = GetOwner();
	FVector Location = Owner->GetActorLocation();
	Location.Z = Height;

	Owner->SetActorLocation(Location, false);
}

float UShelfController::GetTotalMassOnPlate1() {
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors = TArray<AActor*>();
	//find overlapping actors
	if (!PressurePlate1) { return 0; }
	PressurePlate1->GetOverlappingActors(OUT OverlappingActors);
	//add their masses
	for (auto* Actor : OverlappingActors) {
		//this produces a crash somehow, dunno why
		float mass = Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		TotalMass += mass;
		UE_LOG(LogTemp, Warning, TEXT("%s wighing %f on pressureplate %s"),
			*Actor->GetName(), mass,  *GetOwner()->GetName())
	}
	//UE_LOG(LogTemp, Warning, TEXT("actors %s"),TotalMass)
	return TotalMass;
}

float UShelfController::GetTotalMassOnPlate2() {
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors = TArray<AActor*>();
	//find overlapping actors
	if (!PressurePlate2) { return 0; }
	PressurePlate2->GetOverlappingActors(OUT OverlappingActors);
	//add their masses
	for (auto* Actor : OverlappingActors) {
		//this produces a crash somehow, dunno why
		float mass = Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		TotalMass += mass;
		UE_LOG(LogTemp, Warning, TEXT("%s wighing %f on pressureplate %s"),
			*Actor->GetName(), mass,  *GetOwner()->GetName())
	}
	//UE_LOG(LogTemp, Warning, TEXT("actors %s"),TotalMass)
	return TotalMass;
}


