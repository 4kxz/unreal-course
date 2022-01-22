#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly)
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* TrailParticle;

	UFUNCTION()
		void OnHit(
			UPrimitiveComponent* HitComponent,
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComponent,
			FVector Impulse,
			const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
		float Damage = 50.f;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* HitParticles;

	UPROPERTY(EditDefaultsOnly)
		USoundBase* LaunchSound;

	UPROPERTY(EditDefaultsOnly)
		USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCameraShakeBase> CamShakeClass;

};
