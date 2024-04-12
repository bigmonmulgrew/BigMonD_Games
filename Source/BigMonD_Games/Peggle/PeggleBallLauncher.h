// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PeggleBallLauncher.generated.h"

UCLASS()
class BIGMOND_GAMES_API APeggleBallLauncher : public APawn
{
	GENERATED_BODY()
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	// Sets default values for this actor's properties
	APeggleBallLauncher();
	UPROPERTY(VisibleAnywhere, Category = "Sprites");
	class UPaperSpriteComponent* MySprite;
	UPROPERTY(EditAnywhere, Category = "Ammo")
	TSubclassOf<AActor> Ball;
	UPROPERTY(EditAnywhere, Category = "Ammo")
	float ShotPower = 2000.0;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	void MovePlayer(float input);
	void Fire();

};
