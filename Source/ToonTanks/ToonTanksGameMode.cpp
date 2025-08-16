// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"


void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
	
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}



void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank) // Check what type of actor died. If Turret, tally. If Player -> go to lose condition.
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;
		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	}
	
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}
