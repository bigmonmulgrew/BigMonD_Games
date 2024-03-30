// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "BigMonD_Games/Pong/BasePongBat.h"
#include "BreakoutBat.generated.h"

/**
 * 
 */
UCLASS()
class BIGMOND_GAMES_API ABreakoutBat : public ABasePongBat
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void MovePlayer(float input);

};
