// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTrack.h"




void UTankTrack::SetThrottle(float Throttle)
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