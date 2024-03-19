// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePongBat.h"
#include "PlayerPongBat.generated.h"

/**
 * 
 */
UCLASS()
class BIGMOND_GAMES_API APlayerPongBat : public ABasePongBat
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void MovePlayer(float input);
};
