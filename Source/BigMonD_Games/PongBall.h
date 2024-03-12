// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	FVector MyVelocity;
	float HalfPlayFieldHeight;
	float HalfPlayFieldWidth;
	void ChangeDirection(FVector* MyUpdatedLocaiton);
	//void OnCollision();
};
