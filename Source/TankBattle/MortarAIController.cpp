// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"

#include "TankBattle.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "MortarAIController.h"



void AMortarAIController::GetPlayerTank()
{
	ATankPlayerController *PlayerController;
	if (GetWorld()->GetFirstPlayerController())
	{
		PlayerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());
		PlayerTank = PlayerController->GetControlledTank();
	}
	else PlayerTank = nullptr;
}

void AMortarAIController::BeginPlay()
{
	Super::BeginPlay();
	GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Mortar Name: %s"), *GetPawn()->GetName());
		UE_LOG(LogTemp, Warning, TEXT("AI Mortar - Reference to Player Tank: %s"), *PlayerTank->GetName());
		UTankAimingComponent *AutoComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (AutoComponent)
		{
			TankAimingComponent = AutoComponent;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Player Tank Name: %s -- Aiming Component Not Found!"), *GetPawn()->GetName());
		}
	}
}
void AMortarAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (PlayerTank && TankAimingComponent)
	{
		TankAimingComponent->AimAt(PlayerTank->GetActorLocation() + AimingOffset);
		if (TankAimingComponent->FiringState == EFiringState::Ready)
		{
			TankAimingComponent->Fire();
		}
	}
}
