// Fill out your copyright notice in the Description page of Project Settings.


#include "PongBall.h"

#include "BasePongBat.h"
#include "GameManagerPong.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraActor.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

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

	//find the game manager
	GameManagerPong = Cast<AGameManagerPong>(UGameplayStatics::GetActorOfClass(GetWorld(),AGameManagerPong::StaticClass()));
	
	// Calculate the ball width from the sprite
	BallHalfWidth = MySprite->Bounds.GetBox().GetSize().X / 2;
	MyVelocity = FVector(BallSpeed, 0, BallSpeed);
	NormalizeBallVelocity(MyVelocity);
	
	AActor* GameCamera = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
	const UCameraComponent* GameCameraComponent = Cast<ACameraActor>(GameCamera)->GetCameraComponent();
	
	HalfPlayFieldHeight = (GameCameraComponent->OrthoWidth / GameCameraComponent->AspectRatio) / 2;
	HalfPlayFieldWidth  = (GameCameraComponent->OrthoWidth / 2);
	
}

// Called every frame
void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	const FVector DeltaVector = MyVelocity * DeltaTime;
	FVector MyUpdatedLocation = (GetActorLocation() + DeltaVector);

	ChangeDirection(&MyUpdatedLocation);
	
	if(!Scored)	SetActorLocation(MyUpdatedLocation);
	else
	{
		SetActorLocation(FVector::Zero());
		Scored = false;
	}

	
}

void APongBall::ChangeDirection(const FVector* MyUpdatedLocation)
{
	const float VerticalLimit = HalfPlayFieldHeight - EdgeBuffer;
	if     (MyUpdatedLocation->Z + BallHalfWidth >  VerticalLimit)		MyVelocity.Z = -BallSpeed; // Magic number bad
	else if(MyUpdatedLocation->Z - BallHalfWidth < -VerticalLimit)		MyVelocity.Z =  BallSpeed; // Magic number bad
	else if(MyUpdatedLocation->X + BallHalfWidth >  HalfPlayFieldWidth)	GainScore(0); 
	else if(MyUpdatedLocation->X - BallHalfWidth < -HalfPlayFieldWidth)	GainScore(1); 
}

void APongBall::GainScore(int player)
{
	Scored = true;
	GameManagerPong->IncreaseScore(player);
}

void APongBall::NormalizeBallVelocity(FVector& VelToNormalize)
{
	VelToNormalize.Normalize();
	VelToNormalize = VelToNormalize * BallSpeed;
}

void APongBall::OnCollision(UPrimitiveComponent* OverlappedComponent,
                            AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult)
{
	
	ABasePongBat* bat = Cast<ABasePongBat>(OtherActor);
	
	if(bat)
	{
		// Get the center of the bat
		FVector BatCenter = bat->GetActorLocation();
		// Get the extent of the bat (half the height in Z direction)
		FVector BatExtent = MySprite->Bounds.GetBox().GetExtent();
		// Get the impoact point fo the ball
		FVector BallImpactPoint = GetActorLocation();

		// Calculate the relative position of the hit point from the bat's center
		float RelativePosition = (BallImpactPoint.Z - BatCenter.Z) / BatExtent.Z;

		// Clamp the value between -1 and 1 just in case of any floating point imprecision
		RelativePosition = FMath::Clamp(RelativePosition, -1.0f, 1.0f);
		
		MyVelocity.X = -MyVelocity.X; // TODO this is a lazy way to do the collision direction change.
		MyVelocity.Z = (MyVelocity.Z + BallSpeed * RelativePosition) /2;
		NormalizeBallVelocity(MyVelocity);
	}
	 
}
