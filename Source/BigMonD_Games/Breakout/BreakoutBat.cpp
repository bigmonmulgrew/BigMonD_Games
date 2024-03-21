// Copyright 100705789


#include "BreakoutBat.h"

void ABreakoutBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	PlayerInputComponent->BindAxis("Horizontal", this, &ABreakoutBat::MovePlayer);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABreakoutBat::MovePlayer(float input)
{
	SetActorLocation(GetActorLocation() + FVector(1 * input,0,0));
}