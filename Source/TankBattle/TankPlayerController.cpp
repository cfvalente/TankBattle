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
		UE_LOG(LogTemp, Warning, TEXT("Tank name: %s"), *GetControlledTank()->GetName());
	}
	return;
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	return;
}
