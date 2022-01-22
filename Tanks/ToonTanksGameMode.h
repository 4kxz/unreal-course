#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);

	UFUNCTION(BlueprintImplementableEvent)
		void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool bWonGame);

protected:
	virtual void BeginPlay() override;

private:
	class ATank* Tank;
	class AToonTanksPlayerController* PlayerController;
	float StartDelay = 3.f;
	int32 TurretCount = 0;

	void HandleGameStart();
	int32 GetTurretCount();
};
