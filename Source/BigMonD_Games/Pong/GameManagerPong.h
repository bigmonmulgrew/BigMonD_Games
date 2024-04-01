// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "BigMonD_Games/GameManager.h"
#include "GameManagerPong.generated.h"

/**
 * 
 */
UCLASS()
class BIGMOND_GAMES_API AGameManagerPong : public AGameManager
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings");
	float MaxScore = 10;
public:
	void IncreaseScore(int player);
	int Score[2] {0,0};				// Use an array because it supports a flexible number of players for later
};
