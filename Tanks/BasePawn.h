#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();
	void HandleDestruction();

protected:
	void RotateTurret(FVector);
	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* SpawnPoint;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AProjectile> ProjectileClass;


	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* DeathParticles;

	UPROPERTY(EditDefaultsOnly)
		class USoundBase* DeathSound;
};
