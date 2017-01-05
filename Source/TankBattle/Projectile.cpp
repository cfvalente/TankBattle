// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Component"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Component"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	LaunchBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Component"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;
	ImpactBlast->OnSystemFinished.AddDynamic(this, &AProjectile::Finished);
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::Hit);
}

void AProjectile::Hit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ZeroVector);
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();

	UGameplayStatics::ApplyRadialDamage(this, DamageDealt, GetActorLocation(), ExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());
	//FTimerHandle Timer;
	//UE_LOG(LogTemp, Warning, TEXT("OnHit!"));
	//GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimer, Delay, false);
}

void AProjectile::OnTimer()
{
	//UE_LOG(LogTemp, Warning, TEXT("Timer!"));
	return;
}

void AProjectile::Finished(class UParticleSystemComponent* PSystem)
{
	Destroy();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProjectile::LaunchProjectile(float Speed)
{
	float Seconds = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Fire Ok"), Seconds);
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
	LaunchBlast->Activate();
}
