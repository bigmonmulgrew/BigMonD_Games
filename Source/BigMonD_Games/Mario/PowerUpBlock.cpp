// Copyright 100705789


#include "BigMonD_Games/Mario/PowerUpBlock.h"

#include "Mario.h"
#include "PaperSpriteComponent.h"

void APowerUpBlock::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                FVector NormalImpulse, const FHitResult& Hit)
{
	if(MySprite->GetSprite() == PermanentSprite) return; 
	if(OtherActor->IsA(AMario::StaticClass()) && FromUnderside)
	{
		// Schedule the Destroy method to be called on the next tick
		//Do this becuase unreal is aa big baby and will crash if we destroy on the same frame the collision happens
		GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			if(PermanentBlock)SpawnPowerUp();
			else Destroy();
		});
	}
}
void APowerUpBlock::SpawnPowerUp()
{
	
	MySprite->SetSprite(PermanentSprite);

	// Get a reference to the world; from a method where you have access to it
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Set the spawn location and rotation
		FVector Location = GetActorLocation() + FVector(0.0f, 0.0f, 10.0f);
		FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn the actor
		ACollectible* SpawnedActor = World->SpawnActor<ACollectible>(DropPowerUp, Location, Rotation, SpawnParams);
		if (SpawnedActor)
		{
			// Optionally do something with the spawned actor
		}
	}

}