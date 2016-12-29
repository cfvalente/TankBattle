// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	ATank *GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CrossHairYLocation = 0.3333f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LineTraceRange = 1000000.0f;
private:
	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	void InitScreenLocation();
	FVector2D ScreenLocation;
};
