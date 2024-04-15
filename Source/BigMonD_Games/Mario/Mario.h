// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mario.generated.h"

UCLASS()
class BIGMOND_GAMES_API AMario : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMario();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
