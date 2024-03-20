// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPongBat.h"

#include "PongBall.h"
#include "Kismet/GameplayStatics.h"

void AAIPongBat::BeginPlay()
{
	Super::BeginPlay();
	TheBall = UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass());
}

void AAIPongBat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveToBall();
}
void AAIPongBat::MoveToBall()
{
	if (GetActorLocation().Z > TheBall->GetActorLocation().Z)
	{
		SetActorLocation(GetActorLocation() + FVector(0,0,-1));
	}
	if (GetActorLocation().Z < TheBall->GetActorLocation().Z)
	{
		SetActorLocation(GetActorLocation() + FVector(0,0,1));
	}
}
