// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
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
		UTankAimingComponent *AutoComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
		if (AutoComponent)
		{
			TankAimingComponent = AutoComponent;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Player Tank Name: %s -- Aiming Component Not Found!"), *GetControlledTank()->GetName());
		}
	}
}
void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (ATank *ControlledTank = GetControlledTank())
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		//FString Location = ControlledTank->GetActorLocation().ToString();
		//FString Target = PlayerTank->GetActorLocation().ToString();
		//float dist = FVector::Dist(ControlledTank->GetActorLocation(),PlayerTank->GetActorLocation());
		//UE_LOG(LogTemp, Warning, TEXT("\nLocation: %s\nTarget: %s\n Distance: %f"), *Location, *Target, dist);
		TankAimingComponent->AimAt(PlayerTank->GetActorLocation()+AimingOffset);
		if (TankAimingComponent->FiringState == EFiringState::Ready)
		{
			TankAimingComponent->Fire();
		}
	}
}
