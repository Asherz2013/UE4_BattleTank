// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))//, hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
    GENERATED_BODY()

public:
    // -1 is Max downward speed, and +1 is max up movement
    void Elevate(float RelativeSpeed);

private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxDegreesPerSecond = 10.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxElevationDegrees = 40.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MinElevationDegrees = 0.0f;
};
