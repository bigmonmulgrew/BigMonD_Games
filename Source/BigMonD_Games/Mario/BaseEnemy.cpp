// Copyright 100705789


#include "BaseEnemy.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Components//CapsuleComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("My Image"));
	MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>("My Body");
	LeftTrigger = CreateDefaultSubobject<UBoxComponent>("My Left Detector");
	RightTrigger = CreateDefaultSubobject<UBoxComponent>("My Right Detector");
	HeadTrigger = CreateDefaultSubobject<UBoxComponent>("My Head Detector");

	RootComponent = MyBodyCollider;
	MySprite->SetupAttachment(RootComponent);
	LeftTrigger->SetupAttachment(RootComponent);
	RightTrigger->SetupAttachment(RootComponent);
	HeadTrigger->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

