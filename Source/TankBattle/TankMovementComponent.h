// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, category = "Controls")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, category = "Controls")
	void IntendRotate(float Throw);
	
	UFUNCTION(BlueprintCallable, category = "Setup")
	void Initialize(class UTankTrack *LeftTrackToSet, class UTankTrack *RightTrackToSet);

	virtual void RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) override;

private:
	class UTankTrack *LeftTrack = nullptr;
	class UTankTrack *RightTrack = nullptr;
};
