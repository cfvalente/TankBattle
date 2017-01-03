// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EFiringState : uint8
{
	Ready 		UMETA(DisplayName = "Ready"),
	Moving 	UMETA(DisplayName = "Moving"),
	Reloading		UMETA(DisplayName = "Reloading"),
	OutOfAmmo UMETA(DisplayName = "OutOfAmmo")
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStateChange);


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

	void AimAt(FVector HitLocation);

	void SetBarrelLocation();
	UFUNCTION(BlueprintCallable, category = "Setup")
	void SetBarrelLocation(class UTankBarrel *Barrel);

	UFUNCTION(BlueprintCallable, category = "Setup")
	void SetTurretLocation(class UTankTurret *Barrel);

	UPROPERTY(BlueprintReadOnly, category = "Firing")
	EFiringState FiringState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Firing")
	float FireRate = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Firing")
	float LaunchSpeed = 100000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Firing")
	int32 Ammo = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Firing")
	TSubclassOf<class AProjectile> ProjectileBlueprint;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Firing")
	//FStateChange StateChange;

	UFUNCTION(BlueprintCallable, category = "Firing")
	void Fire();
private:
	class UTankBarrel *Barrel = nullptr;
	class UTankTurret *Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
	double LastFireTime = -10000000.0f;

	bool IsReloaded = true;




};
