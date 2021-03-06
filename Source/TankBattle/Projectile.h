// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKBATTLE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void LaunchProjectile(float Speed);

protected:
	UProjectileMovementComponent *ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Projectile")
	UStaticMeshComponent *CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, category = "Projectile") UParticleSystemComponent *LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, category = "Projectile") UParticleSystemComponent *ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, category = "Projectile") URadialForceComponent *ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, category = "Projectile") float DamageDealt = 10.0f;

	UFUNCTION() void Finished(class UParticleSystemComponent* PSystem);
	UFUNCTION() void Hit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);

	UFUNCTION() void OnTimer();

	UPROPERTY(EditDefaultsOnly, category = "Setup")
	float Delay = 0.5f;
	
};
