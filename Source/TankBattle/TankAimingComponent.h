// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void AimAt(FVector HitLocation, float LaunchSpeed);

	void SetBarrelLocation();
	UFUNCTION(BlueprintCallable, category = "Setup")
	void SetBarrelLocation(class UTankBarrel *Barrel);

	UFUNCTION(BlueprintCallable, category = "Setup")
	void SetTurretLocation(class UTankTurret *Barrel);

private:
	class UTankBarrel *Barrel = nullptr;
	class UTankTurret *Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);




};