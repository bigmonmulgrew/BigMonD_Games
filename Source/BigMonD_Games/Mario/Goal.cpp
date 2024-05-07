// Copyright 100705789


#include "BigMonD_Games/Mario/Goal.h"

#include "Mario.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("GoalBodySprite"));
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();

	MySprite->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnOverlap);
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoal::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AMario::StaticClass()))
	{
		UGameplayStatics::OpenLevel(GetWorld(), "L_Win");
	}
}

