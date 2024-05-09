// Copyright 100705789


#include "BreakoutBrick.h"
#include "PaperSpriteComponent.h"

// Sets default values
ABreakoutBrick::ABreakoutBrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;
}

// Called when the game starts or when spawned
void ABreakoutBrick::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABreakoutBrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABreakoutBrick::DecreaseHealth(int damage)
{
	BlockHealth -= damage;
}
