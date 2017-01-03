// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "MortarAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLE_API AMortarAIController : public AAIController
{
	GENERATED_BODY()
	
	
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector AimingOffset = FVector::ZeroVector;
private:
	void GetPlayerTank();
	class ATank *PlayerTank = nullptr;

	class UTankAimingComponent *TankAimingComponent = nullptr;
};
