// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankPlayerController.h"




ATank *ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Name: %s"), *GetControlledTank()->GetName());
		InitScreenLocation();
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrossHair();
}
void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) return;
	FVector HitLocation = FVector::ZeroVector;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}

}
void ATankPlayerController::InitScreenLocation()
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	ScreenLocation = FVector2D(ViewPortSizeX*CrossHairXLocation, ViewPortSizeY*CrossHairYLocation);
}
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	FVector CameraWorldLocation, WorldDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection))
	{
		FHitResult Hit;
		FVector StartLocation = PlayerCameraManager->GetCameraLocation();
		FVector EndLocation = StartLocation + WorldDirection*LineTraceRange;
		if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
		{
			HitLocation = Hit.Location;
			return true;
		}
	}
	return false;
}
