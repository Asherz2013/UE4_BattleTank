// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetPawn(APawn* InPawn) override;

protected:
    
    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
    // Start the tank moving the barrel so that a shot would hit where a crosshair intersects the world
    void AimTowardsCrossHair();

    // Return an OUT parameter, true if hit landscape
    bool GetSightRayHitLocation(FVector& Hitlocation) const;

    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

    bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

    UFUNCTION()
    void OnPossedTankDeath();

    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5f;

    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.33333f;

    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 1000000.0f;
};
