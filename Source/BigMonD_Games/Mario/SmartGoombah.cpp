// Copyright 100705789


#include "BigMonD_Games/Mario/SmartGoombah.h"

#include "Components/BoxComponent.h"

ASmartGoombah::ASmartGoombah()
{
	LeftHoleDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Hole Detector"));
	RightHoleDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Hole Detector"));

	LeftHoleDetector->SetupAttachment(RootComponent);
	RightHoleDetector->SetupAttachment(RootComponent);

}



void ASmartGoombah::BeginPlay()
{
	Super::BeginPlay();
	LeftHoleDetector->OnComponentEndOverlap.AddDynamic(this, &ASmartGoombah::LeftEndOverlap);
	RightHoleDetector->OnComponentEndOverlap.AddDynamic(this, &ASmartGoombah::RightEndOverlap);
}

void ASmartGoombah::LeftEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hole Detected"));
	if(OtherActor->Tags.Contains("Floor")) WalkingDirection = 1;
}

void ASmartGoombah::RightEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("Hole Detected"));
	if(OtherActor->Tags.Contains("Floor")) WalkingDirection = -1;
}