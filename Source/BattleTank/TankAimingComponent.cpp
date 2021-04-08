// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
    // So that first fire is after initial reload
    LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    if (RoundsLeft <= 0)
    {
        FireState = EFiringState::OutOfAmmo;
    }
    else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
    {
        FireState = EFiringState::Reloading;
    }
    else if (IsBarrelMoving())
    {
        FireState = EFiringState::Aiming;
    }
    else
    {
        FireState = EFiringState::Locked;
    }
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (!ensure(Barrel)) { return; }

    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
    (
        this,
        OutLaunchVelocity,
        StartLocation,
        HitLocation,
        LaunchSpeed,
        false,
        .0f,
        .0f,
        ESuggestProjVelocityTraceOption::DoNotTrace
    );

    if(bHaveAimSolution)
    {
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
}

void UTankAimingComponent::MoveBarrelTowards(FVector NewAimDirection)
{
    if (!ensure(Barrel) || !ensure(Turret)) { return; }
    
    AimDirection = NewAimDirection;
    // Work-out difference between current barrel rotation, and NewAimDirection
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    Barrel->Elevate(DeltaRotator.Pitch);
    
    // Always Yaw the shortest way
    if (FMath::Abs(DeltaRotator.Yaw) < 180)
    {
        Turret->Rotate(DeltaRotator.Yaw);
    }
    else
    {
        Turret->Rotate(-DeltaRotator.Yaw);
    }
}

bool UTankAimingComponent::IsBarrelMoving()
{
    if (!ensure(Barrel)) { return false; }
    auto BarrelForward = Barrel->GetForwardVector();
    return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::Fire()
{
    if (FireState == EFiringState::Locked || FireState == EFiringState::Aiming)
    {
        if (!ensure(Barrel)) { return; }
        if (!ensure(ProjectileBluePrint)) { return; }
        // Spawn a projectile on the socket location of the barrel
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBluePrint,
            Barrel->GetSocketLocation(FName("Projectile")),
            Barrel->GetSocketRotation(FName("Projectile"))
            );
        Projectile->LaunchProjectile(LaunchSpeed);
        // Set Last fire
        LastFireTime = GetWorld()->GetTimeSeconds();
        // Remove an Ammo
        RoundsLeft--;
    }
}

EFiringState UTankAimingComponent::GetFiringState() const
{
    return FireState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
    return RoundsLeft;
}
