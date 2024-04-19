// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPongBat.h"

#include "PongBall.h"
#include "Kismet/GameplayStatics.h"

void AAIPongBat::BeginPlay()
{
	Super::BeginPlay();
	TheBall = UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass());
	PaddleSpeed += AISpeedBonus;	// Give the AI a speed boost based on blueprint settings.
}

void AAIPongBat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToBall(DeltaTime);
}
void AAIPongBat::MoveToBall(float DeltaTime)
{
	if(TheBall == nullptr) return;		//Prevent an error when the ball has been deleted when a player wins.
	if (GetActorLocation().Z > TheBall->GetActorLocation().Z)
	{
		SetActorLocation(GetActorLocation() + FVector(0,0,-1 * PaddleSpeed * DeltaTime));
	}
	if (GetActorLocation().Z < TheBall->GetActorLocation().Z)
	{
		SetActorLocation(GetActorLocation() + FVector(0,0,1  * PaddleSpeed * DeltaTime));
	}
}
