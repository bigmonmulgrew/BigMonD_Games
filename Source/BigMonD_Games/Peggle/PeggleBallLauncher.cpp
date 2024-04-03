// Copyright 100705789


#include "BigMonD_Games/Peggle/PeggleBallLauncher.h"

#include "PaperSpriteComponent.h"

// Sets default values
APeggleBallLauncher::APeggleBallLauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;
	AutoPossessPlayer = EAutoReceiveInput::Player0;		//Auto possess the player.
	
}

void APeggleBallLauncher::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	MySprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MySprite->TranslucencySortPriority = 3; 
}


// Called when the game starts or when spawned
void APeggleBallLauncher::BeginPlay()
{
	Super::BeginPlay();
	
}

void APeggleBallLauncher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	PlayerInputComponent->BindAxis("Horizontal", this, &APeggleBallLauncher::MovePlayer);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APeggleBallLauncher::Fire);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Called every frame
void APeggleBallLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APeggleBallLauncher::MovePlayer(float input)
{
	SetActorRotation(GetActorRotation() + FRotator(1 * input, 0, 0));
}

void APeggleBallLauncher::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Firing!"));
	AActor* SpawnedBall = GetWorld()->SpawnActor<AActor>(Ball, GetActorLocation(), GetActorRotation());
	FVector ShotDirection = GetActorUpVector()*= -1;
	SpawnedBall->GetComponentByClass<UPaperSpriteComponent>()->AddImpulse(ShotDirection * ShotPower);
}




