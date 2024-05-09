// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class BIGMOND_GAMES_API AGameManager : public AActor
{
	GENERATED_BODY()
	
protected:
	FTimerHandle LevelReloadTimerHandle;
	float DelayBeforeReload = 8.0f; // Delay in seconds 
public:
	void ReloadLevel();
	void LoadTitle();
};
