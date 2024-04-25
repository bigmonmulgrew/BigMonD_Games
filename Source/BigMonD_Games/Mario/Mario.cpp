// Copyright 100705789


#include "BigMonD_Games/Mario/Mario.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"



void AMario::ConstructorSetupComponents()
{
	MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MarioBodySprite"));
	MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MarioBodyCapsule"));
	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MarioSpringArm"));
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MarioBodyCamera"));
	RootComponent = MyBodyCollider;
	MySprite->SetupAttachment(RootComponent);
	MySpringArm->SetupAttachment(RootComponent);
	MyCamera->SetupAttachment(MySpringArm);
}
void AMario::ConstructorSetupPhysics()
{
	// Setup Physics
	// Enable constraints on the collider
	MyBodyCollider->SetSimulatePhysics(true); // First, enable physics simulation

	// Now, constrain specific axes as needed
	MyBodyCollider->BodyInstance.bLockYTranslation = true; // Lock translation on the Y-axis

	// Lock rotation around all axis
	MyBodyCollider->BodyInstance.bLockXRotation = true;
	MyBodyCollider->BodyInstance.bLockYRotation = true;
	MyBodyCollider->BodyInstance.bLockZRotation = true;

	// After making changes to BodyInstance, we need to update the physics state.
	MyBodyCollider->UpdateBodySetup();
}
// Sets default values
AMario::AMario()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorSetupComponents();

	// Be Lazy, set this all up programatically
	// Rotate the spring arm
	MySpringArm->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	
	ConstructorSetupPhysics();

}

// Called when the game starts or when spawned
void AMario::BeginPlay()
{
	Super::BeginPlay();

	CurrentAnimaitonState = MarioAnimationState::AS_IDLE;
	OldAnimationState = MarioAnimationState::AS_EMPTY;
	ProcessAnimStateMachine();
}

// Called every frame
void AMario::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
	ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -PlayerMaxSpeed, PlayerMaxSpeed);
	MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);

	IdentifyAnimStates();
	ProcessAnimStateMachine();
}

void AMario::IdentifyAnimStates()
{
	// Set old animation state, used to identify changes
	OldAnimationState = CurrentAnimaitonState;

	float Currentspeed = MyBodyCollider->GetPhysicsLinearVelocity().X;

	if		(Currentspeed > 1)  CurrentAnimaitonState = MarioAnimationState::AS_WALKING_RIGHT;
	else if (Currentspeed < -1) CurrentAnimaitonState = MarioAnimationState::AS_WALKING_LEFT;
	else						CurrentAnimaitonState = MarioAnimationState::AS_IDLE;

	
}

void AMario::ProcessAnimStateMachine()
{
	// Check if the state has changed
	if(CurrentAnimaitonState == OldAnimationState) return;

	// Update sprite to match state
	switch (CurrentAnimaitonState)
	{
	case MarioAnimationState::AS_IDLE:
		{
			MySprite->SetFlipbook(Flipbook_Idle);
			break;
		}
	case MarioAnimationState::AS_WALKING_RIGHT:
		{
			MySprite->SetFlipbook(Flipbook_WalkingRight);
			MySprite->SetRelativeRotation(FRotator(0,0,0));
			break;
		}
	case MarioAnimationState::AS_WALKING_LEFT:
		{
			MySprite->SetFlipbook(Flipbook_WalkingRight);
			MySprite->SetRelativeRotation(FRotator(0,180,0));
			break;
		}
	}
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
	if(!bIsJumping)
	{
		MyBodyCollider->AddImpulse(FVector(0,0,1) * JumpForce);
		bIsJumping;
	}
	
}

void AMario::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor->Tags.Contains("Floor")) bIsJumping = false;
}
