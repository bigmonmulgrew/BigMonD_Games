// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "BigMonD_Games/Pong/BasePongBat.h"
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
