// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))//, hidecategories = ("Collision"))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetThrottle(float Throttle);

    // Max force per track in Newtons
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 400000; // Assume 40 tonne tank, and 1g accelleration

private:
    UTankTrack();

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

    virtual void BeginPlay() override;
    
    void ApplySidewaysForce();
    void DriveTrack();

    float CurrentThrottle = 0;
};
