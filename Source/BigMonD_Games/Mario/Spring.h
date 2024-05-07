// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spring.generated.h"

UCLASS()
class BIGMOND_GAMES_API Aspring : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aspring();
	UPROPERTY(VisibleAnywhere, Category = "Sprites")	class UPaperSpriteComponent* MySprite;
	UPROPERTY(EditAnywhere, Category = "Game Balance") float SpringPower= 1000;
	UPROPERTY(VisibleAnywhere, Category = "Collider")	class UBoxComponent* HeadTrigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
