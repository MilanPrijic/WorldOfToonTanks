// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
	
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation()); // Rotate the turret to face the tank.
	}
}

void ATower::CheckFireCondition()
{
	if (Tank == nullptr)
	{
		return;
	}
	if (InFireRange() && Tank->bAlive)
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		const float Distance = FVector::Dist(Tank->GetActorLocation(), GetActorLocation()); // Get the distance between the tank and the tower.
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

