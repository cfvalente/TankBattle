// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, category = "Input")
	void SetThrottle(float Throttle);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UTankTrack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Input")
	float TrackMaxForce = 400000.0f;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);
	
	void ApplySidewaysForce();

	virtual void BeginPlay() override;
	
	float CurrentThrottle = 0.0f;

	void ThrottleForce(float Throttle);

};
