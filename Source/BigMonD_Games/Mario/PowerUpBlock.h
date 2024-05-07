// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "Collectible.h"
#include "BigMonD_Games/Mario/Block.h"
#include "PowerUpBlock.generated.h"

/**
 * 
 */
UCLASS()
class BIGMOND_GAMES_API APowerUpBlock : public ABlock
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Game Balance")	class UPaperSprite* PermanentSprite;
	UPROPERTY(EditAnywhere, Category = "Game Balance")	bool PermanentBlock = true;
	UPROPERTY(EditAnywhere, Category = "Game Balance")	TSubclassOf<ACollectible> DropPowerUp;

protected:
	virtual void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	void SpawnPowerUp();
};
