// Copyright 100705789


#include "BigMonD_Games/Peggle/PegglePowerUpBlock.h"
#include "Kismet/GameplayStatics.h"  // For UGameplayStatics
#include "GameFramework/Actor.h"     // For AActor

void APegglePowerUpBlock::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	switch (PowerUpType)
	{
	case 0:
		CreateMultiball(OtherActor);
		break;
	case 1:
		Pyramid();
		break;
	case 2:
		BigBall(OtherActor);
		break;
	}
}

void APegglePowerUpBlock::CreateMultiball(AActor* OtherActor)
{
	UWorld* World = GetWorld();
	if (!World) return;

	if (!OtherActor) return;

	if (bAlreadyHit) return;	// Incase of collision shenanigans ddont allow to trigger twice

	bAlreadyHit = true;

	// Spawn a new actor at the location of the original actor, with a slight offset to prevent overlapping.
	FVector SpawnLocation = OtherActor->GetActorLocation() + FVector(10.0f, 0.0f, 10.0f);  // Adjust offset as needed
	FRotator SpawnRotation = OtherActor->GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Use the same class as the original ball for the new ball
	AActor* NewBall = World->SpawnActor<AActor>(OtherActor->GetClass(), SpawnLocation, SpawnRotation, SpawnParams);
	if (NewBall)
	{
		// Assuming the ball uses a physics component for movement
		UPrimitiveComponent* OriginalPhysicsComponent = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
		UPrimitiveComponent* NewPhysicsComponent = Cast<UPrimitiveComponent>(NewBall->GetRootComponent());
        
		if (OriginalPhysicsComponent && NewPhysicsComponent)
		{
			// Copy velocity and other physics settings
			NewPhysicsComponent->SetPhysicsLinearVelocity(OriginalPhysicsComponent->GetPhysicsLinearVelocity());
			NewPhysicsComponent->SetPhysicsAngularVelocityInDegrees(OriginalPhysicsComponent->GetPhysicsAngularVelocityInDegrees());

			// Apply an impulse to diverge from the original path
			FVector ImpulseDirection = FVector::UpVector + FMath::VRand().GetSafeNormal(); // Random direction upward
			NewPhysicsComponent->AddImpulse(ImpulseDirection * 500.0f);  // Adjust force magnitude as needed
		}
	}
}

void APegglePowerUpBlock::Pyramid()
{
	UWorld* World = GetWorld();
	if (!World) return;

	if (!PyramidBlueprint) return;

	UE_LOG(LogTemp, Warning, TEXT("Spawning Pyramid"));
	// Example location at the bottom of the screen (you'll need to adjust this based on your game specifics)
	FVector SpawnLocation = FVector(0.0f, 0.0f, 10.0f); // Adjust Z value as per ground level or bottom screen in game world coordinates
	FRotator SpawnRotation = FRotator(0.0f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	// Spawn the Blueprint
	AActor* SpawnedActor = World->SpawnActor<AActor>(PyramidBlueprint, SpawnLocation, SpawnRotation, SpawnParams);
	if (SpawnedActor)
	{
		// Optionally set properties or initiate behaviors
	}
}

void APegglePowerUpBlock::BigBall(AActor* OtherActor)
{
	OtherActor->SetActorScale3D(FVector(2.0f,2.0f,2.0f));
}

