#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	SetPhysicsHandle();
	SetInput();
}

void UGrabber::SetPhysicsHandle()
{
	AActor* Owner = GetOwner();
	PhysicsHandle = Owner->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a physics handle"), *Owner->GetName());
	}
}

void UGrabber::SetInput()
{
	AActor* Owner = GetOwner();
	Input = Owner->FindComponentByClass<UInputComponent>();
	if (!Input)
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a physics handle"), *Owner->GetName());
	}
	else 
	{
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PhysicsHandle)
	{
		return;
	}
	else if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReachLocation());
	}
}

FHitResult UGrabber::GetTarget() const
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		GetPlayerLocation(),
		GetReachLocation(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(""), false, GetOwner())
	);
	return HitResult;
}

FVector UGrabber::GetReachLocation() const
{
	UWorld* World = GetWorld();
	FVector Location;
	FRotator Rotation;
	World->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);
	return Location + Rotation.Vector() * 100.f;
}

FVector UGrabber::GetPlayerLocation() const
{
	UWorld* World = GetWorld();
	FVector Location;
	FRotator Rotation;
	World->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);
	return Location;
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber pressed"));
	FHitResult Hit = GetTarget();
	AActor* Actor = Hit.GetActor();
	if (Actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("HitResult: %s"), *Actor->GetName());
		PhysicsHandle->GrabComponentAtLocation(Hit.GetComponent(), NAME_None, Hit.TraceEnd);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber released"));
	PhysicsHandle->ReleaseComponent();
}