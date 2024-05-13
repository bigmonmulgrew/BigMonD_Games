// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "BigMonD_Games/Peggle/PeggleBlock.h"
#include "PegglePowerUpBlock.generated.h"


UENUM()
enum class PegglePowerUp : uint8
{
	PUP_MULTIBALL,
	PUP_PYRAMID,
	PUP_BIGBALL
};

/**
 * 
 */
UCLASS()
class BIGMOND_GAMES_API APegglePowerUpBlock : public APeggleBlock
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="Power Up") PegglePowerUp PowerUpType = PegglePowerUp::PUP_MULTIBALL;
	UPROPERTY(EditAnywhere, Category="Power Up") UClass* PyramidBlueprint;
protected:
	virtual void OnHit(UPrimitiveComponent* HitComponent,
			   AActor* OtherActor,
			   UPrimitiveComponent* OtherComp,
			   FVector NormalImpulse,
			   const FHitResult& Hit) override;
private:
	bool bAlreadyHit = false;
	void CreateMultiball(AActor* OtherActor);
	void Pyramid();
	void BigBall(AActor* OtherActor);
};
