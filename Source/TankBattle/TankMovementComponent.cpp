// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) return;
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector MoveVelocityNormal = MoveVelocity.GetSafeNormal();
	float Cos = FVector::DotProduct(TankForward, MoveVelocityNormal);
	float Sin2 = FMath::Sqrt(1.0f - FMath::Square(Cos));
	float Sin = -FVector::CrossProduct(TankForward, MoveVelocityNormal).Size()*FMath::Sign(FVector::CrossProduct(TankForward, MoveVelocityNormal).Z);
	float z = FVector::CrossProduct(TankForward, MoveVelocityNormal).Z;
	//float Sin = FVector::CrossProduct(TankForward, MoveVelocityNormal).Z;
	IntendMoveForward(Cos);
	IntendRotate(1.6 * Sin);

	//UE_LOG(LogTemp, Warning, TEXT("\nSin: %f\nSin2: %f\nZ: %f\nCos: %f"), Sin, Sin2, z, Cos);
}

void UTankMovementComponent::IntendRotate(float Throw)
{
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}