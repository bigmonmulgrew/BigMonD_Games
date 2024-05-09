// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakoutBrick.generated.h"

UCLASS()
class BIGMOND_GAMES_API ABreakoutBrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakoutBrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "Sprites") class UPaperSpriteComponent* MySprite;
	UPROPERTY(EditAnywhere, Category = "Game Balance") int BlockHealth = 1;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int GetBrickHealth(){  return BlockHealth;	}	// Leaving this in .h as its just a property wrapper
	void DecreaseHealth(int damage = 1);
};
