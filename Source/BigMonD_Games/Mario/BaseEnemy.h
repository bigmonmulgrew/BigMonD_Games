// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

UCLASS()
class BIGMOND_GAMES_API ABaseEnemy : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Player Properties")
	float BounceForce = 1000; 

	// Sets default values for this actor's properties
	ABaseEnemy();
	UPROPERTY(VisibleAnywhere, Category = "Sprites")	class UPaperFlipbookComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Collider")	class UCapsuleComponent* MyBodyCollider;
	UPROPERTY(VisibleAnywhere, Category = "Collider")	class UBoxComponent* LeftTrigger;
	UPROPERTY(VisibleAnywhere, Category = "Collider")	class UBoxComponent* RightTrigger;
	UPROPERTY(VisibleAnywhere, Category = "Collider")	class UBoxComponent* HeadTrigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
