#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOpenDoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassInside() const;
	void SetAudioComponent();

private:
	float InitialYaw;
	float CurrentYaw;
	UPROPERTY(EditAnywhere)
	float TargetYaw = 90.f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
	float DoorCloseTime = 0.f;
	UPROPERTY(EditAnywhere)
	float DoorDelay = 0.3f;
	UPROPERTY(EditAnywhere)
	UAudioComponent* Audio = nullptr;
	bool OpenPlayed = false;
	bool ClosePlayed = true;
};
