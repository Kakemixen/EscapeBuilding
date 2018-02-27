// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "ShelfController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEBUILDING_API UShelfController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShelfController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate1;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate2;
	UPROPERTY(EditAnywhere)
		float MassThreshold1 = 80.f;
	UPROPERTY(EditAnywhere)
		float MassThreshold2_min = 9.5f;
	UPROPERTY(EditAnywhere)
		float MassThreshold2_max = 10.5f;

	UPROPERTY(VisibleAnywhere)
		float LoweredHeight  = 0.0f;
	UPROPERTY(VisibleAnywhere)
		float Height = 310.0f;

	void LowerObject();

	void RaiseObject();

	float GetTotalMassOnPlate1();

	float GetTotalMassOnPlate2();
	
};
