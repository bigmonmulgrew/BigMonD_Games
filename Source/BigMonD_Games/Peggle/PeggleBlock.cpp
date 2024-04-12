// Copyright 100705789


#include "BigMonD_Games/Peggle/PeggleBlock.h"
#include "PaperSpriteComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"

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
	StartPoint = GetActorLocation();
	EndPoint = StartPoint + OscillationOffeset;
}

void APeggleBlock::RotateObject(float DeltaTime)
{
	// Create a rotator that defines the rotation per second
	FRotator DeltaRotation(1.0f * RotationSpeed * DeltaTime, 0.0f, 0.0f);
	
	// Add this rotation to the actor's current rotation
	AddActorLocalRotation(DeltaRotation);
}

void APeggleBlock::OscillateObject(float DeltaTime)
{
	// Increment the oscillation time
	OscillationTime += DeltaTime;

	// Calculate the oscillation factor using a sine wave
	float SineWave = FMath::Sin(OscillationTime * OscillationSpeed);
	float LerpFactor = (SineWave + 1.f) / 2.f; // Normalize to 0-1 range

	// Linearly interpolate between StartPoint and EndPoint based on LerpFactor
	FVector NewLocation = FMath::Lerp(StartPoint, EndPoint, LerpFactor);

	// Set the actor's location
	SetActorLocation(NewLocation);
}

// Called every frame
void APeggleBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateObject(DeltaTime);

	OscillateObject(DeltaTime);
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
