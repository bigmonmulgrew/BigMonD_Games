// Copyright 100705789


#include "BigMonD_Games/Mario/Coin.h"

#include "Mario.h"
#include "MarioGameMode.h"

void ACoin::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AMario::StaticClass()))
	{
		Super::BeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
		AMarioGameMode::AddScore(ScoreValue);
	}
}
