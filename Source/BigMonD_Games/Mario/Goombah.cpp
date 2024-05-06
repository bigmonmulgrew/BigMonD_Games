// Copyright 100705789


#include "BigMonD_Games/Mario/Goombah.h"
#include "Mario.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

void AGoombah::BeginPlay()
{
	Super::BeginPlay();
	
	LeftTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGoombah::OnLeftOverlap);
	RightTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGoombah::OnRightOverlap);
}

void AGoombah::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Walk();
}

void AGoombah::Walk()
{
	// Exit early if dead
	if(!bIsAlive) return;
	
	MyBodyCollider->AddForce(FVector(1,0,0) * EnemyHorrizontalAcceleration * WalkingDirection);

	FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
	ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -EnemyMaxSpeed, EnemyMaxSpeed);
	MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);
	
}

void AGoombah::OnLeftOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if(OtherActor->Tags.Contains("Floor"))
	{
		WalkingDirection = 1;
	}
}

void AGoombah::OnRightOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Walked into something"));
	if(OtherActor->Tags.Contains("Floor"))
	{
		WalkingDirection = -1;
	}
}


