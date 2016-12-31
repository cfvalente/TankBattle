// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"
#include "TankTurret.h"
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
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
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
	//UE_LOG(LogTemp, Warning, TEXT("Aiming rotation: %s"), *AimAsRotator.ToString());
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
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