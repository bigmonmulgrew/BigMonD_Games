// Copyright 100705789


#include "BreakoutBat.h"

#include "Kismet/GameplayStatics.h"

void ABreakoutBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	PlayerInputComponent->BindAxis("Horizontal", this, &ABreakoutBat::MovePlayer);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABreakoutBat::MovePlayer(float input)
{
	if(input != 0) UE_LOG(LogTemp, Warning, TEXT("Button Pressedm %f"), input);
	SetActorLocation(GetActorLocation() + FVector(1 * input,0,0));
}

