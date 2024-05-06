// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "BigMonD_Games/Mario/Collectible.h"
#include "Coin.generated.h"

/**
 * 
 */
UCLASS()
class BIGMOND_GAMES_API ACoin : public ACollectible
{
	GENERATED_BODY()

public:
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
