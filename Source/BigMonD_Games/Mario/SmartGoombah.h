// Copyright 100705789

#pragma once

#include "CoreMinimal.h"
#include "BigMonD_Games/Mario/Goombah.h"
#include "SmartGoombah.generated.h"

/**
 * 
 */
UCLASS()
class BIGMOND_GAMES_API ASmartGoombah : public AGoombah
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Collider")	class UBoxComponent* LeftHoleDetector;
	UPROPERTY(VisibleAnywhere, Category = "Collider")	class UBoxComponent* RightHoleDetector;
	
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void LeftEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void RightEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
