// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	UFUNCTION(BlueprintCallable, category = "Setup")
	class ATank *GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CrossHairYLocation = 0.3333f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LineTraceRange = 1000000.0f;


	UFUNCTION(BlueprintImplementableEvent, category = "Setup")
	void FoundAimingComponent(class UTankAimingComponent *AimCompRef);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Setup")
	class UTankAimingComponent *TankAimingComponent = nullptr;
private:
	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	void InitScreenLocation();
	FVector2D ScreenLocation;
};
