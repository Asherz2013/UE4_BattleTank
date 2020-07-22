// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    // Move the barrel the right amount this frame
    // Given a max elevation speed, and the frame speed
    RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
    auto ElevationChange = (RelativeSpeed * MaxDegreesPerSecond) * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    // Clamp the values
    auto Elevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
    // Apply the new rotation to the barrel
    SetRelativeRotation(FRotator(Elevation, 0, 0));
}


