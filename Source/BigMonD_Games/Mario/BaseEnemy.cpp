// Copyright 100705789


#include "BaseEnemy.h"

#include "Mario.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Components//CapsuleComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("My Image"));
	MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>("My Body");
	LeftTrigger = CreateDefaultSubobject<UBoxComponent>("My Left Detector");
	RightTrigger = CreateDefaultSubobject<UBoxComponent>("My Right Detector");
	HeadTrigger = CreateDefaultSubobject<UBoxComponent>("My Head Detector");

	RootComponent = MyBodyCollider;
	MySprite->SetupAttachment(RootComponent);
	LeftTrigger->SetupAttachment(RootComponent);
	RightTrigger->SetupAttachment(RootComponent);
	HeadTrigger->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	MyBodyCollider->OnComponentHit.AddDynamic(this, &ABaseEnemy::OnCollision);
	HeadTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnHeadOverlap);
}

void ABaseEnemy::CollisonWhenAlive(AActor* OtherActor, AMario* LocalMario)
{
	if(OtherActor->IsA(AMario::StaticClass()))
	{
		LocalMario->KillMario();
	}
	else if(OtherActor->IsA(ABaseEnemy::StaticClass()))
	{
		if(Cast<ABaseEnemy>(OtherActor)->IsLethalProjectile()) KillEnemy();
	}
}

void ABaseEnemy::CollisionWhenDead(AActor* OtherActor, AMario* LocalMario)
{
	if(OtherActor->IsA(AMario::StaticClass()))
	{
		float CorpsePosition = GetActorLocation().X - LocalMario->GetActorLocation().X;
		int NormalizedValue = (CorpsePosition > 0) ? 1 : ((CorpsePosition < 0) ? -1 : 0);
		MyBodyCollider->AddImpulse(FVector(1,0,0) * NormalizedValue * CorpseForce);
	}
}

void ABaseEnemy::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             FVector NormalImpulse, const FHitResult& Hit)
{
	AMario* LocalMario = Cast<AMario>(OtherActor);
	if(bIsAlive)
	{
		CollisonWhenAlive(OtherActor, LocalMario);
	}
	else if(KickableCorpse)
	{
		CollisionWhenDead(OtherActor, LocalMario);
	}
	
}
void ABaseEnemy::OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Exit early if dead
	if(!bIsAlive) return;
	
	if(OtherActor->IsA(AMario::StaticClass()))
	{
		
		Cast<AMario>(OtherActor)->BounceMario(BounceForce);
		KillEnemy();
	}
}

void ABaseEnemy::KillEnemy()
{
	// Exit early if dead
	if(!bIsAlive) return;

	// Track state so we dont try to kill again.
	bIsAlive = false;

	//Set the animation state
	CurrentAnimaitonState = EnemyAnimationState::AS_DIE;
	ProcessAnimStateMachine();

	//Disble Collision
	if (MyBodyCollider)
	{
		MyBodyCollider->SetSimulatePhysics(true);
		MyBodyCollider->SetPhysMaterialOverride(CorpseMaterial);
		MyBodyCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MyBodyCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);  // or appropriate responses

	}
	
	//Destroy Enemy after a delay
	DestroyWithDelay(Flipbook_Die->GetTotalDuration());
}

void ABaseEnemy::DestroyWithDelay(float Delay)
{
	// Setting the timer with a lambda to destroy the actor
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_DestroyActor, [this]()
	{
		if (IsValid(this))  // Checks if the actor is still valid
		{
			Destroy();
		}
	}, Delay, false);
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Exit early if dead
	if(!bIsAlive) return;

	IdentifyAnimStates();
	ProcessAnimStateMachine();
}

bool ABaseEnemy::IsLethalProjectile()
{
	bool bMovingFast = MyBodyCollider->GetPhysicsLinearVelocity().Size() > ProjectileMinSpeed;

	return KickableCorpse && bMovingFast;
}

void ABaseEnemy::IdentifyAnimStates()
{
	
	// Set old animation state, used to identify changes
	OldAnimationState = CurrentAnimaitonState;
	
	if(bIsJumping) return;
	
	float CurrentSpeed = MyBodyCollider->GetPhysicsLinearVelocity().X;

	if		(CurrentSpeed > 1)  CurrentAnimaitonState = EnemyAnimationState::AS_WALKING_RIGHT;
	else if (CurrentSpeed < -1) CurrentAnimaitonState = EnemyAnimationState::AS_WALKING_LEFT;
	else						CurrentAnimaitonState = EnemyAnimationState::AS_IDLE;

	
}

void ABaseEnemy::ProcessAnimStateMachine()
{
	// Check if the state has changed
	if(CurrentAnimaitonState == OldAnimationState) return;

	// Update sprite to match state
	switch (CurrentAnimaitonState)
	{
	case EnemyAnimationState::AS_IDLE:
		{
			SetAnimState(Flipbook_Idle);
			break;
		}
	case EnemyAnimationState::AS_WALKING_RIGHT:
		{
			SetAnimState(Flipbook_WalkingRight, FRotator(0,0,0));
			break;
		}
	case EnemyAnimationState::AS_WALKING_LEFT:
		{
			SetAnimState(Flipbook_WalkingRight, FRotator(0,180,0));
			break;
		}
	case EnemyAnimationState::AS_JUMP:
		{
			SetAnimState(Flipbook_Jump, MySprite->GetRelativeRotation());
			break;
		}
	case EnemyAnimationState::AS_DIE:
		{
			SetAnimState(Flipbook_Die, MySprite->GetRelativeRotation());
			break;
		}
	}
}

void ABaseEnemy::SetAnimState(UPaperFlipbook* TargetFlipBook,FRotator TargetRotation)
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

void ABaseEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Ensure the timer is cleared when the actor is destroyed or level is unloaded
	if (TimerHandle_DestroyActor.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_DestroyActor);
	}
}