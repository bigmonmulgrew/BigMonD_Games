// Copyright 100705789


#include "BigMonD_Games/Mario/OscillatingHazard.h"
#include "PaperSpriteComponent.h"
#include "Mario.h"

// Sets default values
AOscillatingHazard::AOscillatingHazard()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create the hazard sprite component
    HazardSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("HazardSprite"));
    RootComponent = HazardSprite;

    // Create the endpoint sprite component
    EndpointSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("EndpointSprite"));
    EndpointSprite->SetupAttachment(RootComponent);

    // Set collision to detect overlap with player
    HazardSprite->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    HazardSprite->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void AOscillatingHazard::BeginPlay()
{
    Super::BeginPlay();

    StartPosition = GetActorLocation();
    EndPosition = EndpointSprite->GetComponentLocation();

    // Destroy the endpoint sprite since it's no longer needed
    EndpointSprite->DestroyComponent();

    // Listen for collisions
    HazardSprite->OnComponentBeginOverlap.AddDynamic(this, &AOscillatingHazard::OnCollision);
}

void AOscillatingHazard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    MoveHazard(DeltaTime);
    RotateHazard(DeltaTime);
}

void AOscillatingHazard::RotateHazard(float DeltaTime)
{
    // Create a rotator that defines the rotation per second
    FRotator DeltaRotation(1.0f * RotationSpeed * DeltaTime, 0.0f, 0.0f);
	
    // Add this rotation to the actor's current rotation
    AddActorLocalRotation(DeltaRotation);
}

void AOscillatingHazard::MoveHazard(float DeltaTime)
{
    FVector CurrentPosition = GetActorLocation();
    FVector TargetPosition = bMovingToEndpoint ? EndPosition : StartPosition;

    FVector NewPosition = FMath::VInterpConstantTo(CurrentPosition, TargetPosition, DeltaTime, MovementSpeed);
    SetActorLocation(NewPosition);

    if (FVector::Dist(NewPosition, TargetPosition) <= 1.0f)
    {
        bMovingToEndpoint = !bMovingToEndpoint;  // Reverse direction
    }
}

void AOscillatingHazard::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(OtherActor->IsA(AMario::StaticClass()))
    {
        Cast<AMario>(OtherActor)->KillMario();
    }
}

void AOscillatingHazard::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    //Super::PostEditChangeProperty(PropertyChangedEvent);
    EndpointSprite->SetSprite(HazardSprite->GetSprite());
}