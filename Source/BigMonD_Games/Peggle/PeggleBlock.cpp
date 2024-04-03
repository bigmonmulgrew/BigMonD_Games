// Copyright 100705789


#include "BigMonD_Games/Peggle/PeggleBlock.h"
#include "PaperSpriteComponent.h"

// Sets default values
APeggleBlock::APeggleBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	MySprite->OnComponentHit.AddDynamic(this, &APeggleBlock::OnHit);
	RootComponent = MySprite;
}

// Called when the game starts or when spawned
void APeggleBlock::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APeggleBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APeggleBlock::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Warning, TEXT("HIT!"));
	if(!DestroyTimer.IsValid())
	{
		UE_LOG(LogTemp,Warning,TEXT("Setting Timer"));
		GetWorld()->GetTimerManager().SetTimer(DestroyTimer,						// The timer handle
												this,								// The object running the timer
												&APeggleBlock::DestroyThisObject,	// The method to run on expiring
												1.0,								// Delay in seconds
												false);						// Does Timer loop
	}
}

void APeggleBlock::DestroyThisObject()
{
	Destroy();
}

// runs when the actor is created in the editor
void APeggleBlock::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	MySprite->SetNotifyRigidBodyCollision(true);
}
