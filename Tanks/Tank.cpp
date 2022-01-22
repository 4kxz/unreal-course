#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ATank::Fire);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	Controller = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Controller)
	{
		FHitResult Hit;
		Controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
		RotateTurret(Hit.ImpactPoint);
	}
}

APlayerController* ATank::GetTankController() const
{
	return Controller;
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::Move(float Value)
{
	float Delta = UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector Location(Speed * Delta * Value, 0.f, 0.f);
	AddActorLocalOffset(Location, true);
}

void ATank::Turn(float Value)
{
	float Delta = UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator Rotator(0.f, TurnRate * Delta * Value, 0.f);
	AddActorLocalRotation(Rotator, true);
}