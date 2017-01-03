// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Tank.h"
#include "TankAimingComponent.h"
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
		/*TArray<UTankAimingComponent *> Comps;
		GetControlledTank()->GetComponents(Comps);
		if (Comps.Num() > 0)*/
		UTankAimingComponent *AutoComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
		if(AutoComponent)
		{
			TankAimingComponent = AutoComponent;
			FoundAimingComponent(TankAimingComponent);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Player Tank Name: %s -- Aiming Component Not Found!"), *GetControlledTank()->GetName());
		}
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
		TankAimingComponent->AimAt(HitLocation);
	}
	//else UE_LOG(LogTemp, Warning, TEXT("Aiming Solution not Found!"));

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
