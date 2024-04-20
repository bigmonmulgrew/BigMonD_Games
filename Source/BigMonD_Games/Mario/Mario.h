// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mario.generated.h"

UCLASS()
class BIGMOND_GAMES_API AMario : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMario();
	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperSpriteComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Collider")
	class UCapsuleComponent* MyBodyCollider;
	UPROPERTY(VisibleAnywhere, Category = "Camera Setup")
	class USpringArmComponent* MySpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera Setup")
	class UCameraComponent* MyCamera;

	UPROPERTY(EditAnywhere, Category = "Player Properties")
	float JumpForce = 1000; 
	UPROPERTY(EditAnywhere, Category = "Player Properties")
	float PlayerAcceleration = 1000;
	UPROPERTY(EditAnywhere, Category = "Player Properties")
	float PlayerMaxSpeed = 32;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MovePlayerHorizontal(float value);
	void Jump();

};
