// Copyright 100705789


#include "BigMonD_Games/Mario/spring.h"
#include "Mario.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
Aspring::Aspring()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	HeadTrigger = CreateDefaultSubobject<UBoxComponent>("My Head Detector");
	RootComponent = MySprite;
	HeadTrigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void Aspring::BeginPlay()
{
	Super::BeginPlay();
	HeadTrigger->OnComponentBeginOverlap.AddDynamic(this, &Aspring::OnHeadOverlap);
}

void Aspring::OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AMario::StaticClass()))
	{
		Cast<AMario>(OtherActor)->BounceMario(SpringPower, GetActorUpVector());
	}
}

// Called every frame
void Aspring::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

