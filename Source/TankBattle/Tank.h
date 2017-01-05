// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintPure, category = "Health")
	float GetHealthPercentage() const;

	UFUNCTION() float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser);

	UFUNCTION(BlueprintImplementableEvent, category = "Health")
	void HealthChange();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Setup")
	float HitPoints = 100.0f;

	float StartingHitPoints = 0.0f;

	UFUNCTION() void OnTimer();
};
