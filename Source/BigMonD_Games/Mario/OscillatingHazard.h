// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "OscillatingHazard.generated.h"

UCLASS()
class BIGMOND_GAMES_API AOscillatingHazard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOscillatingHazard();
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sprite for the hazard
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* HazardSprite;

	// Sprite for the endpoint (non-gameplay, editor only)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* EndpointSprite;

	// Original position (start point) and End position
	// Really wanna make these private but theres a good chance wwe inherit later.
	FVector StartPosition;
	FVector EndPosition;

	// Movement speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MovementSpeed = 100.0f;

	// Rotation speed in degrees per second
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed = 90.0f;

	// Helper to control direction
	bool bMovingToEndpoint = true;

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

private:
	void MoveHazard(float DeltaTime);
	void RotateHazard(float DeltaTime);
};
