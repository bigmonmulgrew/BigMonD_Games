// Copyright 100705789


#include "BigMonD_Games/Mario/Block.h"

#include "Mario.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MyImage"));
	BottomTrigger = CreateDefaultSubobject<UBoxComponent>("Impact Detector");
	
	RootComponent = MySprite;
	BottomTrigger->SetupAttachment(RootComponent);
}



// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	BottomTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABlock::OnBottomImpact);
	MySprite->OnComponentHit.AddDynamic(this, &ABlock::OnCollision);
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlock::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor->IsA(AMario::StaticClass()) && FromUnderside)
	{
		// Schedule the Destroy method to be called on the next tick
		//Do this becuase unreal is aa big baby and will crash if we destroy on the same frame the collision happens
		GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
		{
			Destroy();
		});
	}
}


void ABlock::OnBottomImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if(OtherActor->IsA(AMario::StaticClass()))
	{
		FromUnderside = true;
	}
}
