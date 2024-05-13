#include "BreakoutBall.h"

#include "BreakoutBat.h"
#include "BreakoutBrick.h"
#include "PaperSprite.h"
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
	StartingPosition = GetActorLocation();
	
	SetupPlayField();
	
	MyCollider->SetBoxExtent(FVector(BallHalfWidth, BallHalfWidth,BallHalfWidth));

	//find the game manager
	GameManager = Cast<AGameManagerBreakout>(UGameplayStatics::GetActorOfClass(GetWorld(),AGameManagerBreakout::StaticClass()));
}

// Called every frame
void ABreakoutBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector DeltaVector = MyVelocity * DeltaTime;
	FVector MyUpdatedLocation = (GetActorLocation() + DeltaVector);

	ChangeDirection(&MyUpdatedLocation);
	if(!Respawning)	SetActorLocation(MyUpdatedLocation);
	else
	{
		SetActorLocation(StartingPosition);
		Respawning = false;
	}
}

void ABreakoutBall::ChangeDirection(FVector* MyUpdatedLocaiton)
{
	if     (MyUpdatedLocaiton->Z + BallHalfWidth >  HalfPlayFieldHeight)
	{
		MyVelocity.Z = -BallSpeed;
		UGameplayStatics::PlaySoundAtLocation(this, BallSound, GetActorLocation());
	} 
	else if(MyUpdatedLocaiton->Z				 < -HalfPlayFieldHeight) LoseBall(); 
	else if(MyUpdatedLocaiton->X + BallHalfWidth >  HalfPlayFieldWidth)
	{
		MyVelocity.X = -BallSpeed;
		UGameplayStatics::PlaySoundAtLocation(this, BallSound, GetActorLocation());
	} 
	else if(MyUpdatedLocaiton->X - BallHalfWidth < -HalfPlayFieldWidth)
	{
		MyVelocity.X =  BallSpeed;
		UGameplayStatics::PlaySoundAtLocation(this, BallSound, GetActorLocation());
	} 
}

void ABreakoutBall::LoseBall()
{
	UE_LOG(LogTemp, Warning, TEXT("Lives: %i"), GameManager->Lives);
	if(GameManager->Lives <= 0)
	{
		GameManager->GameOver();
		this->Destroy();
	}
	else RespawnBall();
}

void ABreakoutBall::RespawnBall()
{
	GameManager->Lives--;
	if(MyVelocity.Z < 0) MyVelocity.Z *= -1;
	Respawning = true;
}

void ABreakoutBall::DamageBrick(AActor* OtherActor)
{
	//Destroy the brick
	if(Cast<ABreakoutBrick>(OtherActor)->GetBrickHealth() < 1)
	{
		OtherActor->Destroy();	
	}else
	{
		Cast<ABreakoutBrick>(OtherActor)->DecreaseHealth();
	}
}

void ABreakoutBall::HitBrick(AActor* OtherActor)
{
	// Retrieve the PaperSpriteComponent from the brick
	UPaperSpriteComponent* SpriteComponent = Cast<UPaperSpriteComponent>(OtherActor->GetComponentByClass(UPaperSpriteComponent::StaticClass()));
	if (!SpriteComponent) return;  // Safety check

	FVector BrickCenter = OtherActor->GetActorLocation();
	FVector BrickSize = FVector(SpriteComponent->Bounds.GetBox().GetSize().X,
								0.f,
								SpriteComponent->Bounds.GetBox().GetSize().Z); 

	FVector BallLocation = GetActorLocation();
	FVector ImpactVector = BallLocation - BrickCenter;
	FVector NormalizedImpact = ImpactVector / BrickSize;

	// Calculate reflection based on normalized impact vector
	if (fabs(NormalizedImpact.X) > fabs(NormalizedImpact.Z)) {
		MyVelocity.X = (NormalizedImpact.X > 0 ? 1 : -1) * BallSpeed;  // Reflect based on X-axis impact
	} else {
		MyVelocity.Z = (NormalizedImpact.Z > 0 ? 1 : -1) * BallSpeed;  // Reflect based on Z-axis impact
	}

	DamageBrick(OtherActor);
}


void ABreakoutBall::HitBat()
{
	//UE_LOG(LogTemp, Warning, TEXT("I HIT THE BAT"));
	FVector BatPosition = GetActorLocation();
	MyVelocity.Z = BallSpeed;
}

void ABreakoutBall::OnCollision(UPrimitiveComponent* OverlappedComponent,
                                AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                int32 OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult)
{
	if
	(OtherActor->IsA(ABreakoutBat::StaticClass()))
	{
		HitBat();
		UGameplayStatics::PlaySoundAtLocation(this, BallSound, GetActorLocation());
	}
	else if(OtherActor->IsA(ABreakoutBrick::StaticClass()))
	{
		HitBrick(OtherActor);
		UGameplayStatics::PlaySoundAtLocation(this, BallSound, GetActorLocation());
	}
}
