#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKiled)
{
	Super::PawnKilled(PawnKiled);
	APlayerController* PlayerController = Cast<APlayerController>(PawnKiled->GetController());
	if (PlayerController)
	{
		EndGame(false);
		UE_LOG(LogTemp, Warning, TEXT("Player killed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Someone killed"));
		for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
		{
			if (!Controller->IsDead())
			{
				return;
			}
		}
		EndGame(true);
	}
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}