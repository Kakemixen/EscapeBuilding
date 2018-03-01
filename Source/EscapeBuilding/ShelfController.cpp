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
	if (!PressurePlateOuter) { UE_LOG(LogTemp, Error, TEXT("missing outer pressureplate")) }
	if (!PressurePlateInner) { UE_LOG(LogTemp, Error, TEXT("missing inner pressureplate")) }
	
}


// Called every frame
void UShelfController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume every frame
	if (GetTotalMassOnOuterPlate() > MassThreshold1) {
		if (GetTotalMassOnInnerPlate() > MassThreshold2_min && GetTotalMassOnInnerPlate() < MassThreshold2_max) {
			OnOpen.Broadcast();
			UE_LOG(LogTemp, Warning, TEXT("OPEN"));
		}
		else {
			OnClose.Broadcast();
		}
	}
	else {
		OnClose.Broadcast();
	}
}


float UShelfController::GetTotalMassOnOuterPlate() {
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors = TArray<AActor*>();
	//find overlapping actors
	if (!PressurePlateOuter) { return 0; }
	PressurePlateOuter->GetOverlappingActors(OUT OverlappingActors);
	//add their masses
	for (const auto* Actor : OverlappingActors) {
		//this produces a crash somehow, dunno why
		float mass = Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		TotalMass += mass;
		UE_LOG(LogTemp, Warning, TEXT("%s wighing %f on pressureplate outer"),
			*Actor->GetName(), mass)
	}
	//UE_LOG(LogTemp, Warning, TEXT("actors %s"),TotalMass)
	return TotalMass;
}

float UShelfController::GetTotalMassOnInnerPlate() {
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors = TArray<AActor*>();
	//find overlapping actors
	if (!PressurePlateInner) { return 0; }
	PressurePlateInner->GetOverlappingActors(OUT OverlappingActors);
	//add their masses
	for (const auto* Actor : OverlappingActors) {
		//this produces a crash somehow, dunno why
		float mass = Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		TotalMass += mass;
		UE_LOG(LogTemp, Warning, TEXT("%s wighing %f on pressureplate inner"),
			*Actor->GetName(), mass)
	}
	//UE_LOG(LogTemp, Warning, TEXT("actors %s"),TotalMass)
	return TotalMass;
}


