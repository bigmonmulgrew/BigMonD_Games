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
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
