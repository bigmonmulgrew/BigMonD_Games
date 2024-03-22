#include "BreakoutBall.h"

#include "BreakoutBat.h"
#include "BreakoutBrick.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABreakoutBall::ABreakoutBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;

	
	
	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Ball Hit Box"));
	MyCollider->SetCollisionEnabled((ECollisionEnabled::QueryOnly));
	MyCollider->SetupAttachment(RootComponent);
	
	MyCollider->OnComponentBeginOverlap.AddDynamic(this, &ABreakoutBall::OnCollision);

	
}

void ABreakoutBall::SetupPlayField()
{
	// Evil magic numbers.
	AActor* GameCamera = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
	const UCameraComponent* GameCameraComponent = Cast<ACameraActor>(GameCamera)->GetCameraComponent();
	
	HalfPlayFieldHeight = (GameCameraComponent->OrthoWidth / GameCameraComponent->AspectRatio) / 2;
	HalfPlayFieldWidth  = (GameCameraComponent->OrthoWidth / 2);

	
}

// Called when the game starts or when spawned
void ABreakoutBall::BeginPlay()
{
	Super::BeginPlay();

	// Calculate the ball width from the sprite
	BallHalfWidth = MySprite->Bounds.GetBox().GetSize().X / 2;
	
	MyVelocity = FVector(BallSpeed, 0, BallSpeed);

	SetupPlayField();
	
	MyCollider->SetBoxExtent(FVector(BallHalfWidth, BallHalfWidth,BallHalfWidth));
}

// Called every frame
void ABreakoutBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector DeltaVector = MyVelocity * DeltaTime;
	FVector MyUpdatedLocation = (GetActorLocation() + DeltaVector);

	ChangeDirection(&MyUpdatedLocation);
	SetActorLocation(MyUpdatedLocation);
}

void ABreakoutBall::ChangeDirection(FVector* MyUpdatedLocaiton)
{
	if     (MyUpdatedLocaiton->Z + BallHalfWidth >  HalfPlayFieldHeight) MyVelocity.Z = -BallSpeed; // Magic number bad
	else if(MyUpdatedLocaiton->Z - BallHalfWidth < -HalfPlayFieldHeight) MyVelocity.Z =  BallSpeed; // Magic number bad
	else if(MyUpdatedLocaiton->X + BallHalfWidth >  HalfPlayFieldWidth)	 MyVelocity.X = -BallSpeed; // Magic number bad
	else if(MyUpdatedLocaiton->X - BallHalfWidth < -HalfPlayFieldWidth)	 MyVelocity.X =  BallSpeed; // Magic number bad
}

void ABreakoutBall::OnCollision(UPrimitiveComponent* OverlappedComponent,
							AActor* OtherActor, UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex, bool bFromSweep,
							const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Breakout Ball: I hit something"));
	if(OtherActor->IsA(ABreakoutBat::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("I HIT THE BAT"));
		FVector BatPosition = GetActorLocation();
		MyVelocity.Z = BallSpeed;
	}
	else if(OtherActor->IsA(ABreakoutBrick::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("I HIT A BRICK"));

		//Deflect The Ball
		FVector HitDirection = GetActorLocation() - OtherActor->GetActorLocation();
		HitDirection.Normalize();
		if(abs(HitDirection.X) > abs(HitDirection.Z))
		{
			if     (HitDirection.X > 0) MyVelocity.X =  BallSpeed;
			else if(HitDirection.X < 0) MyVelocity.X = -BallSpeed;
		}
		else
		{
			if     (HitDirection.Z > 0) MyVelocity.Z =  BallSpeed;
			else if(HitDirection.Z < 0) MyVelocity.Z = -BallSpeed;
		}
		
		//Destroy the brick
		OtherActor->Destroy();
	}
	
}