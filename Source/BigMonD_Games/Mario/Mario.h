// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mario.generated.h"

UENUM()
enum class MarioAnimationState : uint8
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
class BIGMOND_GAMES_API AMario : public APawn
{
	GENERATED_BODY()

public:
	
	// Sets default values for this pawn's properties
	AMario();
	UPROPERTY(VisibleAnywhere, Category = "Sprites")		class UPaperFlipbookComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Collider")		class UCapsuleComponent* MyBodyCollider;
	UPROPERTY(VisibleAnywhere, Category = "Camera Setup")	class USpringArmComponent* MySpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera Setup")	class UCameraComponent* MyCamera;

	UPROPERTY(EditAnywhere, Category = "Player Properties")	float JumpForce = 1000; 
	UPROPERTY(EditAnywhere, Category = "Player Properties")	float PlayerAcceleration = 1000;
	UPROPERTY(EditAnywhere, Category = "Player Properties")	float PlayerMaxSpeed = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")	class UPaperFlipbook* Flipbook_WalkingRight;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")	class UPaperFlipbook* Flipbook_Idle;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")	class UPaperFlipbook* Flipbook_Jump;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")	class UPaperFlipbook* Flipbook_Attack;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")	class UPaperFlipbook* Flipbook_Die;
	
	UPROPERTY(VisibleAnywhere, Category = "Animaitons")	MarioAnimationState CurrentAnimaitonState;
	UPROPERTY(VisibleAnywhere, Category = "Animaitons")	MarioAnimationState OldAnimationState;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Kill Mario
	void KillMario();

	// Bounce Mario
	void BounceMario(float Force);

	// Getter method for checking if mario is alive
	bool IsAlive() {return bIsAlive; };

private:
	const int KillHeight = -450;
	bool bIsJumping;
	bool bIsAlive = true;
	void MovePlayerHorizontal(float value);
	void Jump();
	void ConstructorSetupPhysics();
	void ConstructorSetupComponents();
	void CheckPlayerHeight();
	void IdentifyAnimStates();
	void ProcessAnimStateMachine();
	void SetAnimState(UPaperFlipbook* TargetFlipBook, FRotator TargetRotation = FRotator(0,0,0));
	
	FTimerHandle TimerHandle_DestroyActor;
	void DestroyWithDelay(float Delay);
};
