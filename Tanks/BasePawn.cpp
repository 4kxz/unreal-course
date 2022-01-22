#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(Capsule);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	}
}

void ABasePawn::RotateTurret(FVector LookAt)
{
	FVector ToTarget = LookAt - TurretMesh->GetComponentLocation();
	TurretMesh->SetWorldRotation(FRotator(0.f, ToTarget.Rotation().Yaw, 0.f));
}

void ABasePawn::Fire()
{
	FVector Location = SpawnPoint->GetComponentLocation();
	FRotator Rotation = SpawnPoint->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}