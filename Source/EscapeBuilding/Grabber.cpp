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

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if grabber has attached object, move said object
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent) {
		FVector LineTraceEnd = GetTraceEnd();

		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::FindPhysicsComponent() {
	///Look for attached physics handler
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == nullptr) {
		//Log Error Physicshandle not found
		UE_LOG(LogTemp, Error, TEXT("%s missing physicshandle"), *GetOwner()->GetName());
	}
}

void UGrabber::SetUpInputComponent() {
	///Look for Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
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
	FHitResult Hit = GetFirstPhysicsBodyInReach();

	///If we hit something, attach that physics
	//atach
	if (Hit.GetActor()) {
		PhysicsHandle->GrabComponent(
			Hit.GetComponent(),
			NAME_None,
			Hit.GetActor()->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("BARG"));
	//TODO release physics body
	PhysicsHandle->ReleaseComponent();

}


const FHitResult UGrabber::GetFirstPhysicsBodyInReach(){
	/// get Player viewpoint this tick
	FVector ViewPointLoc;
	FRotator ViewPointRot;
	GetViewPoint(
		OUT ViewPointLoc, 
		OUT ViewPointRot
	);

	FVector LineTraceEnd = GetTraceEnd();

	///setup query params
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;

	///Ray-Cast/Line trace out to reach distance
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		ViewPointLoc,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	DebugHitActor(Hit);

	return Hit;
}


void UGrabber::GetViewPoint(FVector OUT &Location, FRotator OUT &Rotation) {
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT Location,
		OUT Rotation
	);

	/*///Draw debug gvector
	DrawDebugLine(
	GetWorld(),
	ViewPointLoc,
	LineTraceEnd,
	FColor(0, 0, 255),
	false,
	0.f,
	0.f,
	5.f
	);*/
}

FVector UGrabber::GetTraceStart() {
	FVector ViewPointLoc;
	FRotator ViewPointRot;
	GetViewPoint(
		OUT ViewPointLoc,
		OUT ViewPointRot
	);
	return ViewPointLoc;
}

FVector UGrabber::GetTraceEnd() {
	FVector ViewPointLoc;
	FRotator ViewPointRot;
	GetViewPoint(
		OUT ViewPointLoc,
		OUT ViewPointRot
	);
	return ViewPointLoc + ViewPointRot.Vector()*Reach;
}


void UGrabber::DebugHitActor(FHitResult &Hit)
{
	///See what we hit
	if (Hit.GetActor()) {
		FString HitName = Hit.GetActor()->GetName();
		float Distance = Hit.Distance;

		UE_LOG(LogTemp, Warning, TEXT("Hitting %s,  from CM"),
			*HitName, Distance)
	}
}
