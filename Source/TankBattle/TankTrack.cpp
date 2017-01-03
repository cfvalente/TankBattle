// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"




UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

}

void UTankTrack::BeginPlay()
{
	//Super::BeginPlay();
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

}

void UTankTrack::ApplySidewaysForce()
{
	float Delta = GetWorld()->GetDeltaSeconds();
	UStaticMeshComponent *Root = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	float Mass = Root->GetMass();
	FVector Right = GetRightVector();
	FVector Speed = GetComponentVelocity();
	float SlippageSpeed = FVector::DotProduct(Right, Speed);
	FVector CorrectionAcceleration = -SlippageSpeed / Delta * Right;
	// 2 Tracks --> Força dividida
	FVector CorrectionForce = (Mass / 2.0f) * CorrectionAcceleration;
	Root->AddForce(CorrectionForce);

	auto Time = GetWorld()->GetTimeSeconds();
	FString TankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%f: %s --> %s"), Time, *TankName, *CorrectionForce.ToString());
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp(CurrentThrottle+Throttle, -1.0f, 1.0f);
}

void UTankTrack::ThrottleForce(float Throttle)
{
	auto Time = GetWorld()->GetTimeSeconds();
	FString TankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%f: %f"), Time, Throttle);

	FVector AppliedForce = GetForwardVector() * Throttle * TrackMaxForce;
	FVector ForceLocation = GetComponentLocation();

	UStaticMeshComponent *TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(AppliedForce, ForceLocation);

	//UE_LOG(LogTemp, Warning, TEXT("%f: %s --> %s"), Time, *TankName, *AppliedForce.ToString());
}

void UTankTrack::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	auto Time = GetWorld()->GetTimeSeconds();
	FString TankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%f: %s --> %f"), Time, *TankName, CurrentThrottle);
	ThrottleForce(CurrentThrottle);
	ApplySidewaysForce();
	CurrentThrottle = 0.0f;
}