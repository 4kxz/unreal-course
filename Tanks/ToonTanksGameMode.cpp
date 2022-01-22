#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (PlayerController)
		{
			PlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATurret* DeadTower = Cast<ATurret>(DeadActor))
	{
		DeadTower->HandleDestruction();
		TurretCount--;
		if (TurretCount == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	TurretCount = GetTurretCount();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	StartGame();
	if (PlayerController)
	{
		PlayerController->SetPlayerEnabledState(false);
		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			PlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true);
		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false);
	}
}

int32 AToonTanksGameMode::GetTurretCount()
{
	TArray<AActor*> Turrets;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Turrets);
	return Turrets.Num();
}