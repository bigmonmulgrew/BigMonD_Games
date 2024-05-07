// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class BIGMOND_GAMES_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();
	UPROPERTY(VisibleAnywhere, Category = "Sprites")	class UPaperSpriteComponent* MySprite;
	UPROPERTY(EditAnywhere, Category = "Game Balance")	int ScoreValue = 0;
	UPROPERTY(VisibleAnywhere, Category = "Collider")	class UBoxComponent* BottomTrigger;

protected:
	bool FromUnderside = false;
	UFUNCTION()
	virtual void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnBottomImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
