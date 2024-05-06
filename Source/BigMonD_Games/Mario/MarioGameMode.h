// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MarioGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BIGMOND_GAMES_API AMarioGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	inline static int PlayerScore;

public:
	UFUNCTION(BlueprintCallable) void ResetScore();
	UFUNCTION()					 static void AddScore(int ScoreToAdd);
	UFUNCTION(BlueprintCallable) int GetScore();
	
};
