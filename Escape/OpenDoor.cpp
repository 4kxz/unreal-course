#include "OpenDoor.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

UOpenDoor::UOpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	CurrentYaw = InitialYaw = Owner->GetActorRotation().Yaw;
	TargetYaw += InitialYaw;
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has opendoor but no pressure plate"), *Owner->GetName());
	}
	SetAudioComponent();
}

void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float Time = GetWorld()->GetTimeSeconds();
	if (TotalMassInside() > 100.f)
	{
		OpenDoor(DeltaTime);
		DoorCloseTime = Time + DoorDelay;
	}
	else if (Time > DoorCloseTime)
	{
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime) 
{
	AActor* Owner = GetOwner();
	FRotator Rotation = Owner->GetActorRotation();
	Rotation.Yaw = CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, .5f * DeltaTime);
	Owner->SetActorRotation(Rotation);
	if (Audio)
	{
		if (!OpenPlayed)
		{
			Audio->Play();
			OpenPlayed = true;
			ClosePlayed = false;
		}
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	AActor* Owner = GetOwner();
	FRotator Rotation = Owner->GetActorRotation();
	Rotation.Yaw = CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, 1.5f * DeltaTime);
	Owner->SetActorRotation(Rotation);
	if (Audio)
	{
		if (!ClosePlayed)
		{
			Audio->Play();
			ClosePlayed = true;
			OpenPlayed = false;
		}
	}
}

float UOpenDoor::TotalMassInside() const
{
	float Total = 0.f;
	TArray<AActor*> Actors;
	if (!PressurePlate) return 0.f;
	PressurePlate->GetOverlappingActors(Actors);
	for (AActor* Actor : Actors)
	{
		Total += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return Total;
}

void UOpenDoor::SetAudioComponent()
{
	AActor* Owner = GetOwner();
	Audio = Owner->FindComponentByClass<UAudioComponent>();
	if (!Audio)
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have an audio component"), *Owner->GetName());
	}
}