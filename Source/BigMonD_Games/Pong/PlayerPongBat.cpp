// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPongBat.h"

#include "Math/UnitConversion.h"

void APlayerPongBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPongBat::MovePlayer);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPongBat::MovePlayer(float input)
{
	SetActorLocation(GetActorLocation() + FVector(0,0,1 * input));
}