#include "LevelManager.h"

#include "SNegativeActionButton.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
    
	// Ensure we have a PlayerController to bind input
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		// Enable input from PlayerController
		EnableInput(PlayerController);
        
		// Bind the axis to the LoadLevel function
		InputComponent->BindAxis("LoadLevel", this, &ALevelManager::LoadLevel);
	}
}


void ALevelManager::LoadLevel(const float LevelNo)
{
	switch (static_cast<int>(LevelNo)) {
	case 0:
		// Do nothing if 0
		break;
	case 1:
		UGameplayStatics::OpenLevel(this, "L_Pong");
		break;
	case 2:
		UE_LOG(LogTemp, Warning, TEXT("Level not implemented"));
		break;
	case 3:
		UE_LOG(LogTemp, Warning, TEXT("Level not implemented"));
		break;
	case 4:
		UE_LOG(LogTemp, Warning, TEXT("Level not implemented"));
		break;
	case 5:
		UE_LOG(LogTemp, Warning, TEXT("Level not implemented"));
		break;
	case 6:
		UE_LOG(LogTemp, Warning, TEXT("Level not implemented"));
		break;
	case 7:
		UE_LOG(LogTemp, Warning, TEXT("Level not implemented"));
		break;
	case 8:
		UE_LOG(LogTemp, Warning, TEXT("Level not implemented"));
		break;
	case 9:
		UE_LOG(LogTemp, Warning, TEXT("Level not implemented"));
		break;
	
	default:
		UE_LOG(LogTemp, Warning, TEXT("Loading Title"));
		UGameplayStatics::OpenLevel(this, "L_Title");
		break;
	}
	
}


