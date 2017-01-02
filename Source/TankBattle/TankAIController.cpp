// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankPlayerController.h"
#include "TankAIController.h"




ATank *ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank *ATankAIController::GetPlayerTank() const
{
	ATank *PlayerTank;
	ATankPlayerController *PlayerController;
	if (GetWorld()->GetFirstPlayerController())
	{
		PlayerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
		PlayerTank = PlayerController->GetControlledTank();
	}
	else PlayerTank = nullptr;
	return PlayerTank;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if (GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Name: %s"), *GetControlledTank()->GetName());
		UE_LOG(LogTemp, Warning, TEXT("AI Tank - Reference to Player Tank: %s"), *GetPlayerTank()->GetName());
		PlayerTank = GetPlayerTank();
	}
}
void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (ATank *ControlledTank = GetControlledTank())
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
}
