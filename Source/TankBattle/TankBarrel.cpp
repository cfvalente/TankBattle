// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"




void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	float Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Elevate Working"), Time);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevationm = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(Elevationm, 0, 0));
}