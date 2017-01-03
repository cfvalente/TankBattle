// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	FiringState = EFiringState::Ready;

}



// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	// ...
	if (FiringState == EFiringState::Reloading && (FPlatformTime::Seconds() - LastFireTime) > FireRate)
	{
		IsReloaded = true;
		FiringState = EFiringState::Moving;
	}
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (Barrel)
	{
		FString OurTankName;
		OurTankName = GetOwner()->GetName();

		FVector OutDirection;
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

		if (UGameplayStatics::SuggestProjectileVelocity(this, OutDirection, StartLocation, HitLocation, LaunchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace))
		{
			FVector AimDirection = OutDirection.GetSafeNormal();
			//UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s"), *OurTankName, *AimDirection.ToString());
			MoveBarrelTowards(AimDirection);

			//float Time = GetWorld()->GetTimeSeconds();
			//UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution Working"), Time);
		}
		else
		{
			float Time = GetWorld()->GetTimeSeconds();
			UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution NOT Working"), Time);
		}
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	float Pitch = DeltaRotator.Pitch;
	float Yaw = DeltaRotator.Yaw;
	//if (Pitch > 180.0f) Pitch = Pitch - 360.0f;
	if (Yaw > 180.0f) Yaw = Yaw - 360.0f;
	if (Yaw < -180.0f) Yaw = 360 + Yaw;
	//UE_LOG(LogTemp, Warning, TEXT("Aiming rotation: %s"), *AimAsRotator.ToString());
	Barrel->Elevate(Pitch);
	Turret->Rotate(Yaw);
	if (FiringState != EFiringState::Reloading && FiringState != EFiringState::OutOfAmmo)
	{
		if (!DeltaRotator.IsNearlyZero(0.1f))
		{
			FiringState = EFiringState::Moving;
		}
		else
		{
			FiringState = EFiringState::Ready;
		}
	}
}

void UTankAimingComponent::Fire()
{
		if (Barrel && IsReloaded && ProjectileBlueprint != nullptr && FiringState != EFiringState::OutOfAmmo)
		{
			IsReloaded = false;
			LastFireTime = FPlatformTime::Seconds();
			AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
			Projectile->LaunchProjectile(LaunchSpeed);
			FiringState = EFiringState::Reloading;
			Ammo--;
			if (Ammo == 0) FiringState = EFiringState::OutOfAmmo;
		}
}

void UTankAimingComponent::SetBarrelLocation()
{
	for (UActorComponent *i : GetOwner()->GetComponentsByClass(UTankBarrel::StaticClass()))
	{
		if (i->GetName() == FString("Barrel"))
		{
			Barrel = Cast<UTankBarrel>(i);
			return;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Barrel not found."));
	return;
}

void UTankAimingComponent::SetBarrelLocation(UTankBarrel *Barrel)
{
	this->Barrel = Barrel;
}

void UTankAimingComponent::SetTurretLocation(UTankTurret *Turret)
{
	this->Turret = Turret;
}