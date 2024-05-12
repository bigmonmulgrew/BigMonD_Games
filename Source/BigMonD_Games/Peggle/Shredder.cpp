// Copyright 100705789


#include "BigMonD_Games/Peggle/Shredder.h"

#include "PeggleBallLauncher.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShredder::AShredder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Shredder"));
	RootComponent = MyCollider;
}

void AShredder::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APeggleBallLauncher* BallLauncher = Cast<APeggleBallLauncher>(UGameplayStatics::GetActorOfClass(GetWorld(), APeggleBallLauncher::StaticClass()));
	if (BallLauncher)
	{
		BallLauncher->ReloadBall();
	}
}

// Called when the game starts or when spawned
void AShredder::BeginPlay()
{
	Super::BeginPlay();

	MyCollider->OnComponentBeginOverlap.AddDynamic(this, &AShredder::OnOverlap);
}

// Called every frame
void AShredder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

