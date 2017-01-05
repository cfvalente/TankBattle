// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankMovementComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	StartingHitPoints = HitPoints;
	/*TArray<UActorComponent *> Components = GetComponentsByClass(TSubclassOf<class UStaticMeshComponent>());
	for (auto i : Components)
	{
		if (i->GetName() == FString("Tank"))
		{
			UStaticMeshComponent *Tank = Cast<UStaticMeshComponent>(i);
			SetRootComponent(Tank);
			ExplosionEffect->AttachToComponent(Tank, FAttachmentTransformRules::KeepRelativeTransform);
			return;

		}
	}*/
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser)
{
	if (HitPoints < DamageAmount)
	{
		float SecondsToDie = 0.5f;
		HitPoints = 0;
		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ATank::OnTimer, SecondsToDie, false);
		GetRootComponent()->SetVisibility(false, true);
		DetachFromControllerPendingDestroy();
		//Destroy();
	}
	else HitPoints -= DamageAmount;
	HealthChange();
	UE_LOG(LogTemp, Warning, TEXT("Damage Taken -- HitPoints left: %f"), HitPoints);
	return HitPoints;
}

void ATank::OnTimer()
{
	Destroy();
	return;
}

float ATank::GetHealthPercentage() const
{
	return HitPoints / StartingHitPoints;
}
