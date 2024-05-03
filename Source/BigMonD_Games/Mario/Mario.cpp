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

	// Enable collisions
	MyBodyCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MyBodyCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block); // or ECR_Overlap
	MyBodyCollider->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	MyBodyCollider->OnComponentHit.AddDynamic(this, &AMario::OnCollision);
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

	// Exit early if dead
	if(!bIsAlive) return;
	
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
	
	if(bIsJumping) return;
	
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
			SetAnimState(Flipbook_Idle);
			break;
		}
	case MarioAnimationState::AS_WALKING_RIGHT:
		{
			SetAnimState(Flipbook_WalkingRight, FRotator(0,0,0));
			break;
		}
	case MarioAnimationState::AS_WALKING_LEFT:
		{
			SetAnimState(Flipbook_WalkingRight, FRotator(0,180,0));
			break;
		}
	case MarioAnimationState::AS_JUMP:
		{
			SetAnimState(Flipbook_Jump, MySprite->GetRelativeRotation());
			break;
		}
	case MarioAnimationState::AS_DIE:
		{
			SetAnimState(Flipbook_Die, MySprite->GetRelativeRotation());
			break;
		}
	}
}

void AMario::SetAnimState(UPaperFlipbook* TargetFlipBook, FRotator TargetRotation)
{
	UPaperFlipbook* NewFlipBook = TargetFlipBook;

	if(!bIsAlive)
	{
		NewFlipBook = Flipbook_Die;
	} else if(bIsJumping)
	{
		NewFlipBook = Flipbook_Jump;
	}
	
	MySprite->SetFlipbook(NewFlipBook);
	MySprite->SetRelativeRotation(TargetRotation);
}

void AMario::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	// Called to bind functionality to input
	PlayerInputComponent->BindAxis("Horizontal", this, &AMario::MovePlayerHorizontal);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMario::Jump);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMario::KillMario()
{
	UE_LOG(LogTemp, Warning, TEXT("Mario Dying"));
	// Exit early if dead
	if(!bIsAlive) return;

	// Track state so we dont try to kill again.
	bIsAlive = false;

	//Set the animation state
	CurrentAnimaitonState = MarioAnimationState::AS_DIE;
	ProcessAnimStateMachine();

	//Destroy Mario after a delay
	DestroyWithDelay(Flipbook_Die->GetTotalDuration());
}

void AMario::BounceMario(float Force)
{
	MyBodyCollider->AddImpulse(FVector(0,0,1) * Force);
}

void AMario::DestroyWithDelay(float Delay)
{
	GetWorld()->GetTimerManager().SetTimerForNextTick([this, Delay]()
	{
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_DestroyActor, 
			[this]() { Destroy(); }, 
			Delay, 
			false
		);
	});
}

void AMario::MovePlayerHorizontal(float value)
{
	if(!bIsAlive) return;
	MyBodyCollider->AddForce(FVector(1,0,0) * value * PlayerAcceleration, NAME_None, true );
}

void AMario::Jump()
{
	// Exit early if dead
	if(!bIsAlive) return;
	
	if(!bIsJumping)
	{
		MyBodyCollider->AddImpulse(FVector(0,0,1) * JumpForce);
		bIsJumping = true;
		CurrentAnimaitonState = MarioAnimationState::AS_JUMP;
		ProcessAnimStateMachine();
	}
	
}

void AMario::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// Exit early if dead
	if(!bIsAlive) return;
	
	if(OtherActor->Tags.Contains("Floor"))
	{
		bIsJumping = false;
		CurrentAnimaitonState = MarioAnimationState::AS_IDLE;
	}
}
