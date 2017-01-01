// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, category = "Input")
	void SetThrottle(float Throttle);
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Input")
	float TrackMaxForce = 400000.0f;
};
