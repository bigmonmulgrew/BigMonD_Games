// Copyright 100705789


#include "BigMonD_Games/Mario/Mario.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"

#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMario::AMario()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MarioBodySprite"));
	MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MarioBodyCapsule"));
	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MArioSpringArm"));
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MarioBodyCamera"));
	RootComponent = MyBodyCollider;
	MySprite->SetupAttachment(RootComponent);
	MySpringArm->SetupAttachment(RootComponent);
	MyCamera->SetupAttachment(MySpringArm);

}

// Called when the game starts or when spawned
void AMario::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMario::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
	ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -PlayerMaxSpeed, PlayerMaxSpeed);
	MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);
}

// Called to bind functionality to input
void AMario::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Horizontal", this, &AMario::MovePlayerHorizontal);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMario::Jump);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMario::MovePlayerHorizontal(float value)
{
	MyBodyCollider->AddForce(FVector(1,0,0) * value * PlayerAcceleration, NAME_None, true );
}

void AMario::Jump()
{
	MyBodyCollider->AddImpulse(FVector(0,0,1) * JumpForce);
}

