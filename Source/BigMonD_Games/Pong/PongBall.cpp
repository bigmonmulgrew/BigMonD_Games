// Fill out your copyright notice in the Description page of Project Settings.


#include "PongBall.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APongBall::APongBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;

	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Ball Hit Box"));
	MyCollider->SetBoxExtent(FVector(32, 32,32)); // More evil magic numbers
	MyCollider->SetCollisionEnabled((ECollisionEnabled::QueryOnly));
	MyCollider->SetupAttachment(RootComponent);

	MyCollider->OnComponentBeginOverlap.AddDynamic(this, &APongBall::OnCollision);
	
}

// Called when the game starts or when spawned
void APongBall::BeginPlay()
{
	Super::BeginPlay();

	MyVelocity = FVector(300, 0, 300);

	// Evil magic numbers.
	HalfPlayFieldHeight = (2048 / 1.777) / 2;
	HalfPlayFieldWidth = (2048 / 2);
	
}

// Called every frame
void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
	const FVector DeltaVector = MyVelocity * DeltaTime;
	FVector MyUpdatedLocation = (GetActorLocation() + DeltaVector);

	ChangeDirection(&MyUpdatedLocation);
	
	SetActorLocation(MyUpdatedLocation);

	
}

void APongBall::ChangeDirection(FVector* MyUpdatedLocaiton)
{
	if     (MyUpdatedLocaiton->Z >  HalfPlayFieldHeight) MyVelocity.Z = -300; // Magic number bad
	else if(MyUpdatedLocaiton->Z < -HalfPlayFieldHeight) MyVelocity.Z =  300; // Magic number bad
	else if(MyUpdatedLocaiton->X >  HalfPlayFieldWidth)	 MyVelocity.X = -300; // Magic number bad
	else if(MyUpdatedLocaiton->X < -HalfPlayFieldWidth)	 MyVelocity.X =  300; // Magic number bad
}

void APongBall::OnCollision(UPrimitiveComponent* OverlappedComponent,
							AActor* OtherActor, UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex, bool bFromSweep,
							const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Pong ball: I hit something!"));

	MyVelocity.X = -MyVelocity.X; // TODO this is a lazy way to do the collision direction change.
}