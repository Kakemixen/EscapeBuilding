// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEBUILDING_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CheckAndOpen();


private:
	UPROPERTY(VisibleAnywhere)
		float OpenAngle = 100.0f;
	UPROPERTY(VisibleAnywhere)
		float ClosedAngle = 180.0f;
	UPROPERTY(EditAnywhere)
		AActor* TriggerActor = nullptr; 
	UPROPERTY(Editanywhere)
		ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(EditAnywhere)
		float CloseDelay = 5.f;

	//functions
	void OpenDoor();
	void CloseDoor();

	//stuff
	float LastOpened;
	AActor* Owner = nullptr;

};
