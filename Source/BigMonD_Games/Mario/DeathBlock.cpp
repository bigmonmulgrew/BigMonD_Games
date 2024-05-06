// Copyright 100705789


#include "BigMonD_Games/Mario/DeathBlock.h"
#include "Mario.h"
#include "PaperSpriteComponent.h"



// Sets default values
ADeathBlock::ADeathBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MyImage"));
	RootComponent = MySprite;
	
	MySprite->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MySprite->SetCollisionProfileName(TEXT("BlockAll"));
	MySprite->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

// Called when the game starts or when spawned
void ADeathBlock::BeginPlay()
{
	
	Super::BeginPlay();
	MySprite->OnComponentHit.AddDynamic(this, &ADeathBlock::OnCollision);
}

// Called every frame
void ADeathBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathBlock::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor->IsA(AMario::StaticClass()))
	{
		Cast<AMario>(OtherActor)->KillMario();
	}
}