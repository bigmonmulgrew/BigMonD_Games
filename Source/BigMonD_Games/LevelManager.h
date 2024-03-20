#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"

UCLASS()
class BIGMOND_GAMES_API ALevelManager : public AActor
{
	GENERATED_BODY()

protected:
	// Override BeginPlay to set up input
	virtual void BeginPlay() override;

	// Function to handle level loading based on input
	UFUNCTION()
	void LoadLevel(float input);
};
