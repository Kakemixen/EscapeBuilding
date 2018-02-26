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

	// get Player viewpoint this tick
	FVector ViewPointLoc;
	FRotator ViewPointRot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT ViewPointLoc, 
		OUT ViewPointRot
	);

	//Log out every tick
	/*UE_LOG(LogTemp, Log, TEXT("VPLoc: %s \tVPRot: %s"),
		*ViewPointLoc.ToCompactString(), 
		*ViewPointRot.ToCompactString()
	);*/

	FVector LineTraceEnd = ViewPointLoc + ViewPointRot.Vector()*Reach;

	//Draw degub gvector
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

	//Ray-Cast out to reach distance

	//See what we hit
}

