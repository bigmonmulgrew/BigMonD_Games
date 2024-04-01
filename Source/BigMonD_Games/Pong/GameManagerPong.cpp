// Copyright 100705789


#include "BigMonD_Games/Pong/GameManagerPong.h"
#include "BigMonD_Games/GameManager.h"
#include "PongBall.h"
#include "Kismet/GameplayStatics.h"

void AGameManagerPong::IncreaseScore(int player)
{
	Score[player]++;
	UE_LOG(LogTemp, Warning, TEXT("Player %i Score: %i"), player+1, Score[player]);

	if(Score[player] >= MaxScore)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player %i Wins"), player + 1);

		AActor* Ball = UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass());
		Ball->Destroy();
		
		// Set a timer to call the ReloadLevel function after the delay
		GetWorld()->GetTimerManager().SetTimer(LevelReloadTimerHandle, this, &AGameManager::ReloadLevel, DelayBeforeReload, false);
	}
}
