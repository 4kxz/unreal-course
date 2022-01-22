#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
		float FireRange = 1000.f;

	UPROPERTY(EditAnywhere)
		float FireRate = 2.f;

	class ATank* Tank;
	FTimerHandle FireRateTimerHandle;
	void CheckFireCondition();
	bool IsTankInRange();
};
