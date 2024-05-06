// Copyright 100705789


#include "BigMonD_Games/Mario/Collectible.h"

#include "Mario.h"
#include "PaperSpriteComponent.h"



// Sets default values
ACollectible::ACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MyImage"));
	RootComponent = MySprite;

	MySprite->OnComponentBeginOverlap.AddDynamic(this, &ACollectible::BeginOverlap);
}

// Called when the game starts or when spawned
void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectible::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
	if(OtherActor->IsA(AMario::StaticClass()))
	{
		Destroy();
	}
}
