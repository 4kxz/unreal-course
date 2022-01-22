#include "Projectile.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle"));
	TrailParticle->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), GetActorRotation());
	}
}

void AProjectile::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector Impulse,
	const FHitResult &Hit)
{
	auto ThisOwner = GetOwner();
	if (!ThisOwner)
	{
		Destroy();
		return;
	}
	auto ThisInstigator = ThisOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();
	if (OtherActor && OtherActor != this && OtherActor != ThisOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, ThisInstigator, ThisOwner, DamageTypeClass);
	}
	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
	}
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(), GetActorRotation());
	}
	if (CamShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(CamShakeClass);
	}
	Destroy();
}