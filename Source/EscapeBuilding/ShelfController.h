// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "ShelfController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWallEvent);

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


	UPROPERTY(BlueprintAssignable)
		FWallEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
		FWallEvent OnClose;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlateOuter = nullptr;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlateInner = nullptr;
	UPROPERTY(EditAnywhere)
		float MassThreshold1 = 80.f;
	UPROPERTY(EditAnywhere)
		float MassThreshold2_min = 9.5f;
	UPROPERTY(EditAnywhere)
		float MassThreshold2_max = 10.5f;

	float GetTotalMassOnOuterPlate();

	float GetTotalMassOnInnerPlate();

	
};
