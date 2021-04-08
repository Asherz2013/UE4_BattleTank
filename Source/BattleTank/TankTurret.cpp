// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
    auto RotationChange = (RelativeSpeed * MaxDegreesPerSecond) * GetWorld()->DeltaTimeSeconds;
    auto Rotation = GetRelativeRotation().Yaw + RotationChange;
    // Apply the new rotation to the Turret
    SetRelativeRotation(FRotator(0, Rotation, 0));
}


