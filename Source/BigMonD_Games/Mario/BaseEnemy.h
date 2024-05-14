// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "Mario.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

UENUM()
enum class EnemyAnimationState : uint8
{
	AS_WALKING_RIGHT,
	AS_WALKING_LEFT,
	AS_IDLE,
	AS_ATTACK,
	AS_JUMP,
	AS_DIE,
	AS_EMPTY
};

UCLASS()
class BIGMOND_GAMES_API ABaseEnemy : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Player Properties")	float BounceForce = 1000; 

	// Sets default values for this actor's properties
	ABaseEnemy();
	UPROPERTY(VisibleAnywhere, Category = "Sprites")	class UPaperFlipbookComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Collider")	class UCapsuleComponent* MyBodyCollider;
	UPROPERTY(VisibleAnywhere, Category = "Collider")	class UBoxComponent* LeftTrigger;
	UPROPERTY(VisibleAnywhere, Category = "Collider")	class UBoxComponent* RightTrigger;
	UPROPERTY(VisibleAnywhere, Category = "Collider")	class UBoxComponent* HeadTrigger;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")	class UPaperFlipbook* Flipbook_WalkingRight;	
	UPROPERTY(EditDefaultsOnly, Category = "Animations")	class UPaperFlipbook* Flipbook_Idle;	
	UPROPERTY(EditDefaultsOnly, Category = "Animations")	class UPaperFlipbook* Flipbook_Jump;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")	class UPaperFlipbook* Flipbook_Die;
	UPROPERTY(EditDefaultsOnly, Category = "Physics")	UPhysicalMaterial* CorpseMaterial;
	
	UPROPERTY(VisibleAnywhere, Category = "Animaitons")	EnemyAnimationState CurrentAnimaitonState;
	UPROPERTY(VisibleAnywhere, Category = "Animaitons")	EnemyAnimationState OldAnimationState;

	UPROPERTY(EditAnywhere, Category = "Death")	bool KickableCorpse;
	UPROPERTY(EditAnywhere, Category = "Death")	float CorpseForce = 500;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CollisonWhenAlive(AActor* OtherActor, AMario* LocalMario);
	void CollisionWhenDead(AActor* OtherActor, AMario* LocalMario);
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Kill the goombah/enemy
	void KillEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool bIsAlive = true;
	bool IsLethalProjectile();

private:
	bool bIsJumping;
	float ProjectileMinSpeed = 1.0f;
	FTimerHandle TimerHandle_DestroyActor;
	void DestroyWithDelay(float Delay);
	void IdentifyAnimStates();
	void ProcessAnimStateMachine();
	void SetAnimState(UPaperFlipbook* TargetFlipBook, FRotator TargetRotation = FRotator(0,0,0));
	
};
