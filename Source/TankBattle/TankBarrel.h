// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 20.0f;
	UPROPERTY(EditAnywhere)
	float MaxElevation = 40.0f;
	UPROPERTY(EditAnywhere)
	float MinElevation = 0.0f;
};
