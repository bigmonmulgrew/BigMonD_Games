// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePongBat.h"
#include "AIPongBat.generated.h"

/**
 * 
 */
UCLASS()
class BIGMOND_GAMES_API AAIPongBat : public ABasePongBat
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category= "ReferencedActors")
	class AActor* TheBall;
	UPROPERTY(EditAnywhere, Category= "Game Tuning")
	float AISpeedBonus = 0;

public:
	virtual void BeginPlay() override;
	void MoveToBall(float DeltaTime);
	virtual void Tick(float DeltaTime) override;
};
