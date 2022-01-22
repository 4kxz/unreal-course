#include "Turret.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TimerManager.h"

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsTankInRange())
	{
		RotateTurret(FVector(Tank->GetActorLocation()));
	}
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}

void ATurret::CheckFireCondition()
{
	if (IsTankInRange())
	{
		Fire();
	}
}

bool ATurret::IsTankInRange()
{
	if (Tank)
	{
		return FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange;
	}
	return false;
}