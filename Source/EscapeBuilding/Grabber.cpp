// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT 
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

	UE_LOG(LogTemp, Warning, TEXT("Grapper reporting for duty!"));

	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// get Player viewpoint this tick
	FVector ViewPointLoc;
	FRotator ViewPointRot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT ViewPointLoc, 
		OUT ViewPointRot
	);

	FVector LineTraceEnd = ViewPointLoc + ViewPointRot.Vector()*Reach;

	///Draw degub gvector
	DrawDebugLine(
		GetWorld(),
		ViewPointLoc,
		LineTraceEnd,
		FColor(0, 0, 255),
		false,
		0.f,
		0.f,
		5.f
	);
	///setup query params
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	///Ray-Cast/Line trace out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		ViewPointLoc,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	///See what we hit
	if (Hit.GetActor()) {
		FString HitName = Hit.GetActor()->GetName();
		float Distance = Hit.Distance;

		UE_LOG(LogTemp, Warning, TEXT("Hitting %s,  from CM"),
			*HitName, Distance)
	}
}

