#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGrabber();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY(EditAnywhere)
	UInputComponent* Input = nullptr;
	void SetPhysicsHandle();
	void SetInput();
	FVector GetPlayerLocation() const;
	FVector GetReachLocation() const;
	FHitResult GetTarget() const;
	void Grab();
	void Release();
};
