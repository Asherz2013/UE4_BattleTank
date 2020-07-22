// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    // Round the Damage coming in to a int based on the platform
    int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);

    // Use the "DamagePoints" instead of DamageAmount so we can be sure we are removing an int from an int
    int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

    CurrentHealth -= DamageToApply;
    if (CurrentHealth <= 0)
    {
        OnDeath.Broadcast();
    }

    // Return the Amount of Damage to apply
    return DamageToApply;
}

float ATank::GetHealthPercent() const
{
    return (float)CurrentHealth / (float)StartingHealth;
}