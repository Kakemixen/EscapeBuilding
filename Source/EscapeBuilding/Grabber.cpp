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

	FindPhysicsComponent();
	SetUpInputComponent();
	
	
}

void UGrabber::FindPhysicsComponent() {
	///Look for attached physics handler
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle) {/*Physicshandle found*/ }
	else {
		//Log Error Physicshandle not found
		UE_LOG(LogTemp, Error, TEXT("%s missing physicshandle"), *GetOwner()->GetName());
	}
}

void UGrabber::SetUpInputComponent(){
	///Look for Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("%s has Input component"), *GetOwner()->GetName());
		///Bind input action
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		//Log Error Physicshandle not found
		UE_LOG(LogTemp, Error, TEXT("%s missing Input component"), *GetOwner()->GetName());
	}

}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("GARB"));

	///Try and reach physics bodies
	GetFirstPhysicsBodyInReach();

	///If we hit something, attach that physics
	//TODO atach

}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("BARG"));
	//TODO release physics body

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


const FHitResult UGrabber::GetFirstPhysicsBodyInReach(){
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

	return Hit;
}

