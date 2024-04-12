// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PeggleBlock.generated.h"

UCLASS()
class BIGMOND_GAMES_API APeggleBlock : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APeggleBlock();
	
	UPROPERTY(VisibleAnywhere, Category = "Sprites");
	class UPaperSpriteComponent* MySprite;
	UPROPERTY(EditAnywhere, Category="Control")
	float RotationSpeed =  0;
	UPROPERTY(EditAnywhere, Category="Control")
	float OscillationSpeed =  0;
	UPROPERTY(EditAnywhere, Category="Control")
	FVector OscillationOffeset =  {0,0,0};
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RotateObject(float DeltaTime);
	void OscillateObject(float DeltaTime);
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	FTimerHandle DestroyTimer;
	void DestroyThisObject();
	FVector StartPoint;
	FVector EndPoint;

	// Internal timer to track oscillation phase
	float OscillationTime;
};
