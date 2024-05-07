// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

UCLASS()
class BIGMOND_GAMES_API ACollectible : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Sets default values for this actor's properties
	ACollectible();

	UPROPERTY(VisibleAnywhere, Category = "Sprites")	class UPaperSpriteComponent* MySprite;
	UPROPERTY(EditAnywhere, Category = "Game Balance")	int ScoreValue = 0;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
