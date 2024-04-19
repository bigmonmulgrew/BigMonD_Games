// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePongBat.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "BigMonD_Games/Pong/GameManagerPong.h"
#include "PongBall.generated.h"

UCLASS()
class BIGMOND_GAMES_API APongBall : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent,
					AActor* OtherActor, UPrimitiveComponent* OtherComp,
					int32 OtherBodyIndex, bool bFromSweep,
					const FHitResult& SweepResult);
	// Sets default values for this actor's properties
	APongBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "Sprites");
	class UPaperSpriteComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Sprites");
	class UBoxComponent* MyCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings");
	float BallSpeed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings");
	float EdgeBuffer = 8;   //Amount to reduce teh top and bottom playfield edge by to correspond to image
	AGameManagerPong* GameManagerPong;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	FVector MyVelocity;
	float HalfPlayFieldHeight;
	float HalfPlayFieldWidth;
	float BallHalfWidth;
	bool Scored = false;
	void ChangeDirection(const FVector* MyUpdatedLocation);
	void GainScore(int player);
	//void OnCollision();
	void NormalizeBallVelocity(FVector& MyVelocity);
	float GetRelativePosition(ABasePongBat* bat);
};
