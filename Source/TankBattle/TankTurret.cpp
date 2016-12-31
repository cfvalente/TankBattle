// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTurret.h"




void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	float Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Rotate Working"), Time);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.0f, NewRotation, 0.0f));
}