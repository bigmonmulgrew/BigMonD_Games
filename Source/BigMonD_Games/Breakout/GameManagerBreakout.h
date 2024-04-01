// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "BigMonD_Games/GameManager.h"
#include "GameManagerBreakout.generated.h"

/**
 * 
 */
UCLASS()
class BIGMOND_GAMES_API AGameManagerBreakout : public AGameManager
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings");
	int Lives = 3;
	void GameOver();
};
