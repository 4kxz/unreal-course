#include "WorldPosition.h"
#include "GameFramework/Actor.h"

UWorldPosition::UWorldPosition()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	FString ObjectPosition = Owner->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("The position is: %s"), *ObjectPosition);
	UE_LOG(LogTemp, Warning, TEXT("Object name is: %s"), *Owner->GetName());
}


void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

