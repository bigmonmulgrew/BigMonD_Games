// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "BigMonD_Games/Mario/BaseEnemy.h"
#include "Goombah.generated.h"

/**
 * 
 */
UCLASS()
class BIGMOND_GAMES_API AGoombah : public ABaseEnemy
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Enemy Settings")	float EnemyHorrizontalAcceleration = 1000;
	UPROPERTY(EditAnywhere, Category = "Enemy Settings")	float EnemyMaxSpeed = 100;
	UPROPERTY(EditAnywhere, Category = "Enemy Settings")	bool StartWalkingRight = false;
protected:
	float WalkingDirection = -1;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnLeftOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnRightOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	void Walk();
	
};
