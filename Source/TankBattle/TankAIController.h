// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	class ATank *GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AcceptanceRadius = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector AimingOffset = FVector::ZeroVector;
private:
	class ATank *GetPlayerTank() const;
	class ATank *PlayerTank;
	class UTankAimingComponent *TankAimingComponent = nullptr;
};
