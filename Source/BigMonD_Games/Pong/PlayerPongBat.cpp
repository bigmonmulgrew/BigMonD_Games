// Copyright 100705789


#include "PlayerPongBat.h"

void APlayerPongBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPongBat::MovePlayer);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPongBat::MovePlayer(float input)
{
	SetActorLocation(GetActorLocation() + FVector(0,0,input * PaddleSpeed * DT));
}